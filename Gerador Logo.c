#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int pgFileSize(FILE *fp);
int pgReadFile(char **response, char *filename); 
int criarArquivo(char texto);

void main(){
	int ret = 0, i = 0,j = 0;
	char *p = NULL;
	char caminho[100];
   
    //Definição do arquivo que será formatado.
	printf("File Name:");
	gets(caminho);	
	
	
	//Chamada da função para pegar os dados do arquivo.
	ret = pgReadFile(&p, caminho);
	
	//Caso a função retorne erro.
	if(ret < 0)
	{
		printf("no data to read");
	}
	
	//Caso retorne sucesso.
	else
	{
		//Imprime os dados do arquivo
		printf("file content [%s]\n\n\n", p);
		
		//definição dos vetores auxiliares
		char *aux = NULL;// vetor que irá receber o texto sem formatação
    	char txt[strlen(p)];//vetor que irá receber o texto formatado
    	
		//Passa os dados do arquivo para a variavel auxiliar a partir do caracter '='
		aux = strstr(p, "=");
		
	
	
	
		//Loop que verifica os dados do arquivo para colocar apenas os caracteres uteis na variavel com o texto formatado
		for (i=1; i <= strlen(p); i++){
	
	  			if(aux[i] !=' ' && aux[i] != ',' &&  aux[i] !=  'x' && (aux[i] != 0 && aux[i+1] != 'x') &&aux[i] != '\n' && aux[i] != '{' && aux[i] != '}' && aux[i] != NULL && aux[i] !=  ';'){
					//if(aux[i]==0 && aux[i+1] != 'x'){
					
						txt[j] = aux[i];
					
						j++;
					//}
		 		
				}
	
		
		}
		
		
		//informa os dados depois de formatados
		printf("Formatted Data: %s\n", txt);
	
		printf("Creating File\n"); 
		
		//chamada da função para criar o arquivo txt
		ret = pgWriteFile(strlen(txt), txt, "logox2.txt");
		
		//caso retorne erro
		if(ret = 0)
		printf("Failed to created file.");
		
		//casso retone sucesso
		else
		printf("File created.\nFile Name: logox2.txt \n");
		system("pause");
	
	    //limpa a memoria do vetor
	    free(p);
	    free(aux);
		
	}






}


int pgFileSize(FILE *fp) {
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    fseek(fp,prev,SEEK_SET);
    return sz;
}

int pgReadFile(char **response, char *filename){
	int size = 0;


	FILE *fileret = NULL;
	
	fileret = fopen(filename, "r+");

	if(fileret == NULL){
		printf("File does not exist.");
		return -1;
	}

	size = pgFileSize(fileret);

	if(size <= 0){
	printf("Error size [%i]", size);
		return size;
	}

	printf("Filesize is %i", size);

	*response = (char*)malloc(size);

	if (*response == NULL){
		printf("Error malloc reading. Returning .");
		return -2;
	}
	

	memset(*response, 0, size + 2);
	fread((char*)*response, sizeof(char), size, fileret);
	fclose(fileret);



	return size;
}

int pgWriteFile(int contentLen, const char *content, char *filename)
{
	int filehandle = 0, ret = 0;
	char _filename[128];
	va_list args;
	FILE *fileret = NULL;


		if ((fileret = fopen(filename, "w+")) == NULL){
			printf("Erro [%i] fopen '%s' file. Errno [%i]", filehandle, _filename, errno);
			return -1;
		}



	if ((ret = fwrite(content, 1, contentLen, fileret)) < 0){
		printf("Error [%i] fwrite '%s' file. Lenght [%i]. Errno [%i]", ret, _filename, contentLen, errno);
		return ret;
	}

printf("Saved %i bytes", ret);

	fclose(fileret);
	return 0;
}

