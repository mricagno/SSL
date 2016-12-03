//DIRECTIVAS AL PREPROCESADOR
#include<stdio.h>
#define MAXLENGTH 1024

//ESTADOS DEL AUTOMATA
enum states {
	NO_COMMENT,
	POSSIBLE_COMMENT,
	LINE_COMMENT,
	COMMENT,
	POSSIBLE_END_OF_COMMENT
};

//DECLARACION DE FUNCIONES
int get_line(char s[], int max);
int read_char_in_nc_state(char char_from_input_array);
int read_char_in_pc_state(char char_from_input_array);
int read_char_in_lc_state(char char_from_input_array);
int read_char_in_comment_state(char char_from_input_array);
int read_char_in_peoc_state(char char_from_input_array);

int main()
{
	int 	len,
		input_char,
		function_return;

	char 	input_array[MAXLENGTH];

	enum states state;

	input_char=0;
	state=NO_COMMENT;

	puts("Ingresar el codigo. Apretar Ctrl+D para finalizar:\n");
	puts("\n----------------------------------------\n");

	while((len=get_line(input_array,MAXLENGTH))>0)
	{
		while(input_array[input_char]!='\0')
		{
			function_return=0;
			switch(state)
			{
			case NO_COMMENT:
				function_return=read_char_in_nc_state(input_array[input_char]);
				if(function_return==POSSIBLE_COMMENT)
				{
					state=POSSIBLE_COMMENT;
					break;
				}
				putchar(input_array[input_char]);
			break;
			case POSSIBLE_COMMENT:
				function_return=read_char_in_pc_state(input_array[input_char]);
				if(function_return==NO_COMMENT){
					state=NO_COMMENT;
				} else if (function_return==LINE_COMMENT){
					state=LINE_COMMENT;
				} else if (function_return==COMMENT){
					state=COMMENT;
				}
			break;
			case LINE_COMMENT:
				function_return=read_char_in_lc_state(input_array[input_char]);
				if(function_return==NO_COMMENT)
					state=NO_COMMENT;
			break;
			case COMMENT:
				function_return=read_char_in_comment_state(input_array[input_char]);
				if(function_return==POSSIBLE_END_OF_COMMENT)
					state=POSSIBLE_END_OF_COMMENT;
			break;
			case POSSIBLE_END_OF_COMMENT:
				function_return=read_char_in_peoc_state(input_array[input_char]);
				if(function_return==COMMENT){
					state=COMMENT;
					break;
				} else if (function_return==NO_COMMENT){
					state=NO_COMMENT;
					break;
				}
			}
			input_char++;	//Para poder trabajar con el siguiente caracter en la proxima iteracion
		}
	}
	return 0;
}	//Fin de la FUNCION MAIN


//DEFINICION DE FUNCIONES INVOCADAS
//---------------------------------------------------------
int get_line(char s[], int max){

	int i,j,k;

	for(j=0,k=0;(i=getchar())!=EOF;++j)
		if(j<max-1)
			s[k++]=i;
	s[k]='\0';

	return k;

}	//La funcion lee el array ingresado por el usuario
//----------------------------------------------------------

int read_char_in_nc_state(char char_from_input_array){
	if(char_from_input_array=='/')
		return POSSIBLE_COMMENT;

	return NO_COMMENT;

}	//La funcion analiza si el caracter que se recibe puede indicar el inicio de un comentario
//----------------------------------------------------------

int read_char_in_pc_state(char char_from_input_array){
	if(char_from_input_array!='/' && char_from_input_array!='*')
		return NO_COMMENT;

	if(char_from_input_array=='/')
		return LINE_COMMENT;

	return COMMENT;	//Si no es un No Comentario, ni es un Comentario de Linea, entonces es un Comentario

}	//La funcion analiza si el caracter que se recibe hace que se pase a un comentario de varias lineas, de una linea, o que no sea un comentario
//----------------------------------------------------------
int read_char_in_lc_state(char char_from_input_array){
	if(char_from_input_array!='\n')
		return LINE_COMMENT;

	return NO_COMMENT;

}	//La funcion analiza si el caracter que se lee es un salto de linea (fin del comentario de linea) o no
//-----------------------------------------------------------
int read_char_in_comment_state(char char_from_input_array){
	if(char_from_input_array=='*')
		return POSSIBLE_END_OF_COMMENT;

	return COMMENT;

}	//La funcion analiza si el caracter puede ocasionar un fin de comentario o no
//-----------------------------------------------------------
int read_char_in_peoc_state(char char_from_input_array){
	if(char_from_input_array=='/')
		return NO_COMMENT;

	return COMMENT;
}	//La funcion analiza si finalizo el comentario o no
