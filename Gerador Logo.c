#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int pgFileSize(FILE *fp);
int pgReadFile(char **response, char *filename); 
int criarArquivo(char texto);
void setDirectory(char *path);

void main(){
	int ret = 0, i = 0,j = 0;
	char *p = NULL;
	char caminho[100];
	char nome[100];
	char resp;
	int ctr2 = 0;
	int ctr = 0;
	char auxDirec = "\\";
	FILE *formFile = NULL;

   
    //Definição do arquivo que será formatado.
	
	
	
	printf("File Path: ");
	gets(caminho);
	
	
	//Chamada da função para pegar os dados do arquivo.
	ret = pgReadFile(&p, caminho);
	
	//Caso a função retorne erro.
	if(ret < 0)
	{
		printf("\nWrong path or fille name. Try again.\n\n");
		main();
	}

	//Caso retorne sucesso.
	else
	{
	
	//Parte de definição do nome de arquivo de saida		
	do{
		//solicita o nome do arquivo desejado pelo usuario
		printf("\nDefine the formated name(default: logo): ");
		gets(nome);
		//limpa o buffer do teclado
		fflush(stdin);
		
		//caso o usuario não digite um valor, ele saira com o nome logo.txt
		if( (strcmp(nome, "")) == 0 ){
			strcat(nome, "logo.txt");
		}
		
		//pega o nome que o usuario definiu e adiciona a extenção ".txt"
		else{
		strcat(nome, ".txt");
					
			
		}
		
		//Verificar se ja possui um arquivo com aquele nome no diretorio.
		if((formFile = fopen(nome, "r")) != NULL ){
			do{
				
				//caso encontre um arquivo com o mesmo nome, pergunta se deseja sobreescrever o arquivo original ou não
				printf("\n%s File name already exist, overwrite?\n Y/N ", nome);
				scanf("%c", &resp);
				fflush(stdin);
					if (resp == 'Y' || resp == 'y'){ 
						ctr2 =1;
						ctr=1;
						
					
				}
				
				 else if(resp == 'n' || resp == 'N' )
				 ctr2 = 1;
				 
				 //Quando o usuario insere um caracter não previsto
				 else
				 printf("\n Invalid answer \n");
			}while(ctr2 == 0);
		}
		else
		ctr=1;
		
		
	
		fclose(formFile);
	
		
	}while(ctr == 0);
	ctr=0;
	ctr2=0;
		
		/*//Imprime os dados do arquivo
		printf("file content [%s]\n\n\n", p);*/
		
		//Informa o Inicio do processo
		printf("\nFormating Fille...\n");
		
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
				else 
				continue;
	
		
		}
		
		
		/*//informa os dados depois de formatados
		printf("Formatted Data: %s\n", txt);*/
	
		printf("\nCreating File...\n"); 
		printf("%s",caminho);
		
		
		//chamada da função para criar o arquivo txt
		if(strstr(caminho, "\\")!=NULL){
			setDirectory(caminho);
			
			strcat(caminho, nome);
			printf("%s", caminho);
			system("pause");
			ret = pgWriteFile(strlen(txt), txt, caminho);
			
			
			
		}	
		else{
				ret = pgWriteFile(strlen(txt), txt, nome);
			
		}
		
		//caso retorne erro
		if(ret = 0)
			printf("Failed to created file.");
			
		//casso retone sucesso
		else
			printf("\nFile created.\nFile Name: 'Formated Fille.txt'.");
			printf("\nCleaning pointers\n.... ");
	
		
		//Limpa ponteiros com dados do arquivo ja formatado
	    free(p);
	    strcpy(aux, ""); 
	    
	    //Pergunta se deseja formatar um outro arquivo.
	do{
		
		printf("\nAnother fille?\n Y/N: ");
		scanf("%c", &resp);
		//caso o usuario deseje formatar mais um arquivo, retorna para o inicio da aplicação.
		if (resp == 'Y' || resp == 'y'){
			main();
			break;
		}
		
		//caso nao tenha mais arquivo para formatar, encerra o aplicativo
		else if(resp == 'n' || resp == 'N'){
			printf("closing app...");
			ctr = 1;
		}
		//caso o usuario digite um caracter não previsto
		else{
			printf("\nInvalid answer \n");
		 }
		 fflush(stdin);
	}while(ctr == 0);
		ctr=0;

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

void setDirectory(char *path){
	char *p1 = path;
	char *p2 = &path[strlen(path) - 1];

	while (p2[0] != '\\') {
		p2--;
	}

	char finalPath[128];
	memset(finalPath, 0, sizeof(finalPath));
	strncpy(finalPath, p1, p2 - p1);
	strcat(finalPath, "\\");
	printf("%s", finalPath);
	strcpy(path, finalPath);
	printf("%s", path);
	system("pause");
}
