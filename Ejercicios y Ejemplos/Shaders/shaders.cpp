#include "main.h"
#include <cerrno>

//Funcion que lee un archivo con codigo de shader y lo
//devuelve como cadena.
char* readShaderSource(const char* source) {
	FILE* fp = fopen(source, "r");
	if (!fp) return NULL;

	fseek(fp, 0L, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	char* buf = (char*) malloc(sizeof(char)*(size+1));

	fread(buf, 1, size, fp);
	buf[size] = '\0';
	return buf;
}

//Funcion que inicializa un shader y regresa un objeto GLSL
GLuint initShader(const char* vShaderf, const char* fShaderf){
	//Creamos el objeto programa GLSL.
	GLuint prog = glCreateProgram();
	const char* shaderSource[] = {fShaderf, vShaderf};

	for (int i = 0; i < 2; i++){
		//obtenemos los shaders como cadena.
		char* source = readShaderSource(shaderSource[i]);
		//Revisar que si se leyo el archivo
		if (source == NULL){
			printf("Failed to read %s\n", shaderSource[i]);
			exit(EXIT_FAILURE);
		}

		//Se crean y compilan los shaders
		GLuint shader = glCreateShader(GL_FRAGMENT_SHADER + i);
		glShaderSource(shader, 1, (const GLchar**) &source, NULL);
		glCompileShader(shader);

		//Revisar que si se compilo el shader
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled){
			printf("%s failed to compile:\n", shaderSource[i]);
			GLint logSize;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
			char logMsg[logSize];
			glGetShaderInfoLog(shader, logSize, NULL, logMsg);
			printf("%s\n", logMsg);
			exit(EXIT_FAILURE);
		}
		//borramos las cadenas generadas.
		free(source);
		//Asociamos los shaders al programa.
		glAttachShader(prog, shader);
	}
	//Linking y ver si hubo algun error.
	glLinkProgram(prog);
	GLint linked;
	glGetProgramiv(prog, GL_LINK_STATUS, &linked);
	if (!linked) {
		printf("Shader program failed to link\n");
		GLint logSize;
		glGetShaderiv(prog, GL_INFO_LOG_LENGTH, &logSize);
		char logMsg[logSize];
		glGetShaderInfoLog(prog, logSize, NULL, logMsg);
		printf("%s\n", logMsg);
		exit(EXIT_FAILURE);
	}
	return prog;	//regresamos el ID del programa GLSL
}

//Funcion que carga un modelo .obj y lo devuelve
//El .obj debe tener puras caras triangulares.
Mesh * createMesh(const char *file)
{
	//abrimos el archivo
	FILE *in = fopen(file, "r");
	if (!in) {
 		printf("The file %s was not found.", file);
 		return NULL;
	}
	//numero de vertices, normales, texturas y caras
	int nv = 0, nn = 0, nt = 0, nf = 0;
	Mesh * o = (Mesh *) malloc(sizeof(Mesh));
	char trash[1024];	//buffer basura
	char type;			//tipo de dato

	//Leemos el archivo para contar el numero de datos.
	while(fscanf(in, "%c", &type) != EOF) {
		switch(type) {
			case 'v':	fscanf(in, "%c", &type);
						//dependiendo del tipo lo contamos
						if (type == ' ') nv++;
						else if (type == 'n') nn++;
						else if (type == 't') nt++;
						fgets(trash, sizeof(trash), in); break;
			case 'f':	fgets(trash, sizeof(trash), in); nf += 3; break;
			default :	fgets(trash, sizeof(trash), in);
		}
 	}

	//Agregamos estos datos al mesh
	o->numv = nv;
	o->numi = nf;
	o->verts = (Vertex *) calloc(nv + 1, sizeof(Vertex));
	o->indices = (unsigned int *) calloc(nf + 1, sizeof(unsigned int));

	//Regresamos al inicio del archivo.
	fseek(in, 0L, SEEK_SET);
	nv = nf = nn = nt = 0;
	//Leemos el archivo para guardar los datos.
	while(fscanf(in, "%c", &type) != EOF) {
		if (type == 'v') {
			fscanf(in, "%c", &type);
			float x, y, z;
			switch (type){
				//vector posicion
				case ' ':	fscanf(in, "%f %f %f\n", &x, &y, &z);
							o->verts[nv].pos = glm::vec3(x, y, z);
							nv++; break;
				//vector textura
				case 'n':	fscanf(in, " %f %f %f\n", &x, &y, &z);
							o->verts[nn].normal = glm::vec3(x, y, z);
							nn++; break;
				//vector normal
				case 't':	fscanf(in, " %f %f\n", &x, &y);
							o->verts[nt].texpos = glm::vec2(x, y);
							nt += (nt < nv? 1:0); break;
			}
		}
		else if (type == 'f'){
			unsigned int tr;	//variable basura
			//por los tipos que encontramos el formato es distinto
			if (nn && nt)
				fscanf(in, " %u/%u/%u %u/%u/%u %u/%u/%u", &o->indices[nf], &tr, &tr
														  , &o->indices[nf+1], &tr, &tr
														  , &o->indices[nf+2], &tr, &tr);
			else if (nn && !nt)
				fscanf(in, " %u//%u %u//%u %u//%u", &o->indices[nf], &tr
													, &o->indices[nf+1], &tr
													, &o->indices[nf+2], &tr);
			else if (!nn && nt)
				fscanf(in, " %u/%u %u/%u %u/%u", &o->indices[nf], &tr
												 , &o->indices[nf+1], &tr
												 , &o->indices[nf+2], &tr);
			else
				fscanf(in, " %u %u %u", &o->indices[nf], &o->indices[nf+1], &o->indices[nf+2]);
			nf+= 3;
			fgets(trash, sizeof(trash), in);
		}
		//de otro modo solo leemos la linea
		else
			fgets(trash, sizeof(trash), in);
 	}

	//cerramos el archivo
	fclose(in);

	//restamos cada valor del indice (epieza en 0)
	for (int i = 0; i < nf; i++)
		o->indices[i]--;

	//Creamos los VAO, VBO y EBO del mesh
	glGenVertexArrays(1, &(o->VAO));
    glGenBuffers(1, &(o->VBO));
    glGenBuffers(1, &(o->EBO));

	//se asocian los VBO y EBO al VAO del mesh
    glBindVertexArray(o->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, o->VBO);
    glBufferData(GL_ARRAY_BUFFER, o->numv * sizeof(Vertex), &(o->verts[0]), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, o->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, o->numi * sizeof(unsigned int),
                 &(o->indices[0]), GL_STATIC_DRAW);

    //posiciones de vertices
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    //normales de vertices
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    //texturas de los vertices
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texpos));

	//activamos otro VAO por defecto
    glBindVertexArray(0);

    return o;
}

//Dibuja un Mesh en pantalla
void drawMesh(Mesh *o) {
	glBindVertexArray(o->VAO);	//activamos el VAO del mesh
	glDrawElements(GL_TRIANGLES, o->numi, GL_UNSIGNED_INT, 0);	//dibujamos el mesh
	glBindVertexArray(0);	//activamos otro VAO por defecto
}

//Libera la memoria dinamica que ocupa un mesh.
void elimMesh(Mesh *o) {
	//Borramos los VBO, EBO y VAO
	glDeleteBuffers(1, &o->VBO);
	glDeleteBuffers(1, &o->EBO);
	glDeleteVertexArrays(1, &o->VAO);
	//Liberamos memoria
	free(o->verts);
	free(o->indices);
	free(o);
}
