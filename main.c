/*Este � um Banco de dados conforme foi requerido na disciplina de APC, e de acordo com o PDF relacionado.
*/

#include <stdio.h>      //Bibliotecas usadas no programa.
#include <stdlib.h>
#include <locale.h>     //Essa biblioteca ser� usada para o uso de acentos.
#include <ctype.h>      //Usada para leitura e manipula��o de strings/caracteres.
#include <string.h>     //https://fresh2refresh.com/c-programming/c-strings/c-strupr-function/ biblioteca de referencia, usada para manipular strings
#define tamanho 999     //Tamanho padr�o.

void cabecalho();       //As fun��es do programa que ser�o explicadas conforme forem chamadas, ou em seu pr�prio c�digo.
void cadastrar_estados();
int checar_estado(char nome_estado[]);
void cadastrar_cidade();
int (checar_cidade(char estado[], char cidade[]));
void cadastrar_pessoa();
int valida_data(int dia, int mes, int ano);
void listar_estado();
void listar_cidade();
void listar_nome();
int compara_nome(char nome_user[], char nome_registro[]);
void relatorio_demografico();

// Escopos globais usados no programa.
typedef struct estado ESTADO;
struct estado {
	char nome_estado[tamanho];
};

typedef struct cidade CIDADE;
struct cidade {
	char nome_cidade[tamanho];
};

typedef struct pessoa PESSOA;
struct pessoa {
    char nome_pessoa[tamanho];
    char sexo;
    int dia, mes, ano;
};

int main()                                                  //Fun��o main que executa o menu principal, e leva as demais subfun��es.
{                                                           //As subfun��es depois de executadas sempre retornam ao main.
    setlocale(LC_ALL, "Portuguese");
    int optionMenu;     //Essa � a vari�vel para a escolha do usu�rio a partir do menu, e leva para uma fun��o equivalente.
    cabecalho();
    printf("------------------------------------------------------------------\n");
    printf("------Banco de Dados----------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    printf("------Digite-o-n�-da-op��o-desejada-------------------------------\n");
    printf("------------------------------------------------------------------\n");
    printf("------1 - Cadastrar Estado----------------------------------------\n");     //Para que seja registrado uma pessoa ou cidade, � necessrio um cadastro pr�vio de um estado.
    printf("------2 - Cadastrar Cidade----------------------------------------\n");     //Resgistro de cidade em um estado j� existente, e necess�rio para o cadastro de uma pessoa.
    printf("------3 - Cadastrar Pessoa----------------------------------------\n");     //Registro de pessoa, com
    printf("------4 - Listar pessoas por Estado-------------------------------\n");
    printf("------5 - Listar pessoas por Cidade-------------------------------\n");
    printf("------6 - Consultar Pessoa por Nome-------------------------------\n");
    printf("------7 - Gerar Relat�rio Demogr�fico-----------------------------\n");
    printf("------8 - Finalizar Programa--------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
    printf("------------------------------------------------------------------\n");
	printf("Digite o n�mero da op��o desejada: ");
	fflush(stdin);      //Coloquei v�rios fflush() ao decorrer do programa para evitar erros com buffers do teclado.
    scanf("%d", &optionMenu);       //Ap�s o menu a variavel � lida e leva � switch.
	do {
        switch (optionMenu){        //Switch que define as escolhas do menu.
                case 1:
                    cadastrar_estados();        //Aqui � levado � fun��o de cadastro de Estado.
                break;
                case 2:
                    cadastrar_cidade();     //Leva para a fun��o de cadastro de Cidade.
                break;
                case 3:
                    cadastrar_pessoa();
                break;
                case 4:
                    listar_estado();
                break;
                case 5:
                    listar_cidade();
                break;
                case 6:
                    listar_nome();
                break;
                case 7:
                    relatorio_demografico();
                break;
                case 8: //Op��o caso o usu�rio queira sair do programa.

                    printf("Muito obrigado, e tenha um bom dia!\n");
                    printf("Aperte qualquer tecla para continuar...\n");
                    fflush(stdin);
                    getchar();      //getchar()'s como esse ser�o usados para que ocorra uma pausa na tela, para que o usu�rio leia alguma mensagem.
                    exit(0);
                break;
                default:		//O default resolver� se for digitado um numero diferente dos disnponiveis no menu.
                    printf("Op��o inv�lida.\nAperte quaquer tecla para continuar...\n");
                    fflush(stdin);
                    getchar();
                    main();
	    }
    }while (optionMenu != 8);       //� feito uma repet��o pra que caso o usu�rio escreva um n�mero diferente dos disponiveis, o programa reinicia o switch
    return 0;
  }

void finalizar() {                                          //Fun��o tempor�ria para que o programa seja finalizado a qualquer momento.
	system("cls");
	printf("Obrigado por utilizar o programa!\nAperte qualquer tecla para continuar...\n\n");
	fflush(stdin);
	getchar();
	exit(0);
}

void cabecalho(){                                           //A fun��o cabe�alho � chamada para limpar a tela e deixar o programa visualmente mais bonito.
	system("cls");
    printf("------------------------------------------------------------------\n");
    printf("-----Instituto de Pesquisa C. C. C. P.----------------------------\n");
    printf("-----Banco de Dados Demogr�fico-----------------------------------\n");
    printf("------------------------------------------------------------------\n\n\n");
}

void cadastrar_estados(){                                   //Fun��o que organiza e registra os Estados do programa.
    FILE* arquivo;
    ESTADO est;
    char cmd_repeat;        //Var�avel que possibilita cadastrar outro estado antes de voltar ao menu.

    arquivo = fopen("lista_estados.txt", "a+");     //Arquivo que � registrado os estados.



    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
        fflush(stdin);
        getchar();
        main();
    }
    cabecalho();
    fflush(stdin);
    printf("Digite o nome do Estado a ser registrado: ");
    fgets(est.nome_estado, tamanho, stdin);
    strupr(est.nome_estado);        //Essa linha transforma a string em mai�scula, pra que seja pesquisado depois.

    if(checar_estado(est.nome_estado) == 0){        //Teste para checagem do arquivo.
        fprintf(arquivo, "%s", est.nome_estado);      //Registro no arquivo do nome do estado digitado.
        printf("\nO estado foi cadastrado com sucesso!\n");
    } else {
        printf("\nO estado j� foi cadastrado.\n");      //Caso o estado ja tenha sido cadastrado, ele n�o o registra novamente, e manda o usu�rio para o final da fun��o.
    }

    fclose(arquivo);        //Arquivo � fechado

    printf("Deseja Cadastrar outro estado? S/N\n");     //Op��o pra caso o usu�rio queira registrar outro estado, ou voltar ao menu
    fflush(stdin);                                      //� lido uma variavel cmd_repeat, que se for igual a letra em quest�o volta ao �nicio da fun��o
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'S'){
        cadastrar_estados();
    }   else {
        main();
    }
}

int checar_estado(char estado_user[]){                           //Fun��o que checa o arquivo para que n�o ocorram registros identicos.
    FILE* arquivo;
    arquivo = fopen("lista_estados.txt", "r");      //abertura do arquivo de estados no modo "read".

    ESTADO est;
    int checkin = 0;        //Esse ser� o contador que retornar� 0 se n�o estiver registado e 1 se ja estiver.

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
        fflush(stdin);
        getchar();
        main();
    } else {
            while (!feof(arquivo)){     //While que confere at� o final do arquivo.
                fgets(est.nome_estado, sizeof(ESTADO), arquivo);
                if(strcmp(est.nome_estado, estado_user) == 0 && checkin == 0){
                    checkin = 1;
                }
            }
    }

    fclose(arquivo);
    return checkin;     //retorno do resultado da fun��o para a fun��o de cadastro de estados.
}

void cadastrar_cidade(){                                    //Fun��o para cadastro de cidades.
    ESTADO est;
    CIDADE city;
    char cmd_repeat;        //Vari�vel para repetir a fun��o, ir para a fun��o cadastrar_estado, ou voltar ao menu.

    cabecalho();
    printf("Obs.: Para que seja registrada uma cidade � necess�rio o registro de um estado previamente.\n");        //Leitura do nome do estado, para registro da cidade.
    printf("Digite o nome do Estado em que a cidade ser� registrada: ");
    fflush(stdin);
    fgets(est.nome_estado, 30, stdin);

    strupr(est.nome_estado);        //Essa linha transforma a string em mai�scula, pra que seja pesquisado depois.

    if(checar_estado(est.nome_estado) == 0){        //Teste para checagem do arquivo.
        printf("\nO estado n�o foi cadastrado.\n");
    }else if (checar_estado(est.nome_estado) == 1){
        FILE* arquivo;          //Esse ponteiro de arquivo � utilizado em todo o programa, de forma universal, mas chamado em todas as fun��es.
        arquivo = fopen("lista_cidades.txt", "a+");
        if (arquivo == NULL){
                printf("\nErro ao executar o arquivo referente �s cidades...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
                fflush(stdin);
                getchar();
                main();
        }
        printf("\nO estado j� foi cadastrado.\n");
        printf("Digite o nome da cidade a ser registrada: ");
        fflush(stdin);
        fgets(city.nome_cidade, 30, stdin);     //Leitura da cidade a ser registrada
        strupr(city.nome_cidade);
        if(checar_cidade(est.nome_estado, city.nome_cidade) == 0){      //Teste para checagem do arquivo.
            fprintf(arquivo, "%s%s\n", est.nome_estado, city.nome_cidade);      //Registro no arquivo do nome da cidade digitado.
            printf("\nA cidade foi cadastrada com sucesso!\n");                 //A cidade � registrada como "ESTADOCIDADE" de forma seguida para a checagem posterior.
        } else {                                                                //Assim � poss�vel se diferenciar cidades com mesmo nome, mas de estados diferentes
            printf("\nA cidade j� foi cadastrada.\n");
        }
        fclose(arquivo);
    }
    printf("\nVoc� pode voltar ao menu, cadastrar um estado, ou cadastrar outra cidade\n");
    printf("Digite: 'E' para cadastrar um estado.\n");      //Pequeno menu de op��es que leva o usu�rio para outras fun��es ou retorna ao �nicio essa.
    printf("Digite: 'C' para cadastrar outra cidade.\n");
    printf("Tecle qualquer outra coisa para retornar ao menu. \n");
    fflush(stdin);
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'C'){
        cadastrar_cidade();     //Retorna para o inicio da fun��o.
    } else {
        if (cmd_repeat == 'E'){
            cadastrar_estados();        //Leva para o registro de estado.
        } else {
            main();     //Retorna ao menu principal.
        }
    }
}

int (checar_cidade(char estado_user[], char cidade_user[])){          //Fun��o que checa o arquivo para que n�o ocorram registros identicos.
    FILE* arquivo;
    arquivo = fopen("lista_cidades.txt", "r");      //abertura do arquivo de estados no modo "read".

    ESTADO est;
    CIDADE city;
    int checkin = 0;        //Esse ser� o contador que retornar� 0 se n�o estiver registado e 1 se ja estiver.

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
        fflush(stdin);
        getchar();
        main();
    } else{
        while (!feof(arquivo)){     //While que confere at� o final do arquivo.
            fgets(est.nome_estado, sizeof(ESTADO), arquivo);        //A cada linha o comando fgets vai pegar o estado e a cidade e checar se coincidem com o que o usuario quer registrar.
            if(strcmp(est.nome_estado, estado_user) == 0){                //If que � gerado para evitar erros ao adquirir dados. E conferir se a cidade foi digitada no mesmo estado.
                fgets(city.nome_cidade, sizeof(CIDADE), arquivo);
                if(strcmp(city.nome_cidade, cidade_user) == 0 && checkin == 0){
                    checkin = 1;        //Caso encontrar alguma linha igual.
                }
            }
        }
    }

    fclose(arquivo);
    return checkin;     //retorno do resultado da fun��o para a fun��o de cadastro de estados.
}

void cadastrar_pessoa(){                                    //Fun��o para o cadastro de pessoas. Feito a partir de uma cidade, que esteja cadastrada em um estado, ja cadastrado.
    FILE* arquivo;
    arquivo = fopen("lista_pessoas.txt", "a+");      //Arquivo em que s�o registradas as pessoas

    ESTADO est;     //As estruturas usadas nessa fun��o.
    CIDADE city;
    PESSOA pes;
    char cmd_repeat;        //Vari�vel para o submenu, que possibilita o cadastro de mais pessoas, ou a entrada em outras op��es do menu principais.

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de pessoas
        fflush(stdin);
        getchar();
        main();
    }

    cabecalho();
    printf("Digite o nome do estado que a pessoa ser� registrada: ");            //� necess�rio que seja registrado previamente o estado.
    fflush(stdin);
    fgets(est.nome_estado, tamanho, stdin);
    strupr(est.nome_estado);

    if(checar_estado(est.nome_estado) == 0){        //Teste para checagem do arquivo se o estado ja foi registrado.
        printf("\nO estado n�o foi cadastrado.\n");     //Caso n�o tenha sido, o usuario vai para o fim da fun��o
    }else if (checar_estado(est.nome_estado) == 1){
        printf("\nO estado j� foi cadastrado.\n");
        printf("Digite o nome da cidade que a pessoa ser� registrada: ");       //� necess�rio que seja registrado previamente.
        fflush(stdin);
        fgets(city.nome_cidade, tamanho, stdin);
        strupr(city.nome_cidade);

        if (checar_cidade(est.nome_estado, city.nome_cidade) == 0){
            printf("\n Esta cidade ainda n�o foi cadastrada.");                 //Se a cidade n�o tiver sido cadastrada, o usu�rio vai para o final da fun��o.
        } else if (checar_cidade(est.nome_estado, city.nome_cidade) == 1){
            printf("\nA cidade j� foi cadastrada.\n");
            printf("Agora ser� necess�rio a data de nascimento da pessoa\n");
            printf("Digite apenas n�meros, no formato DD/MM/AAAA\n");
            printf("Data de nascimento: ");
            fflush(stdin);
            fscanf(stdin, "%2d/%2d/%4d", &pes.dia, &pes.mes, &pes.ano);         //o fscanf � feito no formato DD/MM/AAAA
            if (valida_data(pes.dia, pes.mes, pes.ano) == 0){                   //E a data � validada a partir da fun��o auxiliar
                printf("\n Esta n�o � uma data v�lida.\n");
            } else if (valida_data(pes.dia, pes.mes, pes.ano) == 1) {           //Caso a data n�o esteja no formato deduzido, o usu�rio vai para o final da fun��o
                printf("\n Esta � uma data v�lida.\n");
                printf("Agora digite o sexo da pessoa(M para masculino, F para feminino, O para outro): ");     //Pessoalmente n�o sou de levantar nenhuma bandeira ou de fazer quest�o sobre, mas s� ta ai uma outra op��o.
                do{
                    fflush(stdin);
                    pes.sexo = getchar();
                    pes.sexo = toupper(pes.sexo);
                } while(pes.sexo != 'M' && pes.sexo != 'F' && pes.sexo != 'O'); //Caso o usu�rio digite qualquer coisa que n�o seja o ditado, o programa s� ira scanear novamente at� ser de um formato v�lido.
                printf("\n Digite agora o nome: ");
                fflush(stdin);
                fgets(pes.nome_pessoa, tamanho, stdin);
                strupr(pes.nome_pessoa);

                fprintf(arquivo, "%s%s%s%d/%d/%d-%c\n", est.nome_estado, city.nome_cidade, pes.nome_pessoa, pes.dia, pes.mes, pes.ano, pes.sexo);       //Formato que � registrado no arquivo:
                                                                                                                                                        //ESTADO\nCIDADE\nNOME\nDD/MM/AAAA-S
                printf("\nA pessoa foi cadastrada com sucesso!\n");                                                                                     //S =  caractere equivalente ao sexo.
                fflush(stdin);                                                                                                                          //E os \n s�o adquiridos pelo pr�prio usu�rio.
                getchar();
            }
        }
    }
    fclose(arquivo);

    printf("\nVoc� pode voltar ao menu, cadastrar um estado, cadastrar uma cidade, ou cadastrar outra pessoa\n");
    printf("Digite: 'E' para cadastrar um estado.\n");      //Pequeno menu de op��es que leva o usu�rio para outras fun��es ou retorna ao �nicio essa.
    printf("Digite: 'C' para cadastrar uma cidade.\n");
    printf("Digite 'P' para cadastrar outra pessoa.\n");
    printf("Tecle qualquer outra coisa para retornar ao menu. \n");
    fflush(stdin);
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'C'){
        cadastrar_cidade();     //Leva a fun��o cadastrar_cidade.
    } else {
        if (cmd_repeat == 'E'){
            cadastrar_estados();        //Leva para o registro de estado.
        } else if (cmd_repeat == 'P') {
            cadastrar_pessoa();     //Retorna ao �nicio da fun��o.
        } else {
            main();     //Retorna ao menu principal.
        }
    }
}

int valida_data(int dia, int mes, int ano){                 //Fun��o auxiliar do cadastro de pessoas, checa se uma data digitada � valida ou n�o, necess�ria para o relat�rio demogr�fico.
    int checkin = 0;                                  //Por padr�o a data n�o � v�lida, caso ela esteja no formato permitido ela � validada.
    if (ano >= 1900 && ano <= 2021){
        if (mes <= 12 && mes >= 1){
            if (dia <= 31 && dia <= 31){
                if (dia >= 1 && dia <= 28 && mes == 2){
                    checkin = 1;                      //Caso de fevereiro
                }
                if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12){
                    checkin = 1;                      //Meses de 31 dias
                }
                if (mes == 4 || mes == 6 || mes == 9 || mes == 11){
                    checkin = 1;                      //Meses de 30 dias, s�o validados, mas se tiverem dia 31 voltam a n�o ser validos.
                    if (dia == 31){
                        checkin = 0;
                    }
                }
            }
        }
    }


    return checkin;                                   //Retorno da fun��o 0 = n�o � v�lida e 1 = data v�lida.
}

void listar_estado(){                                       //Fun��o que lista todas as pessoas cadastradas em um estado digitado pelo usu�rio.
    char cmd_repeat, estado_pesquisa[tamanho];      //Vari�vel de repeti��o da fun��o, e o estado a ser listado.
    int contador = 0;                       //Vari�vel que conta o n�mero de pessoas que foram exibidas ao usu�rio.
    PESSOA pes;
    ESTADO est;
    CIDADE city;

    FILE* arquivo;
    arquivo = fopen("lista_pessoas.txt", "r");      //Arquivo em que foi registrado as pessoas.

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
        fflush(stdin);
        getchar();
        main();
    }

    cabecalho();
    printf("Digite o nome do estado a ser pesquisado: ");       //Leitura do estado a ser pesquisado.
    fflush(stdin);
    fgets(estado_pesquisa, tamanho, stdin);
    strupr(estado_pesquisa);                                    //Linha que transforma a string em ma�uscula.
                                                                //Essa linha foi repetida em todas as strings registradas, assim � irrelevante o usuario digitar em mai�sculas ou min�sculas.
    printf("\nAs pessoas que foram cadastradas neste estado foram:\n");
    printf("------------------------------------------------------------------\n");

    while (!feof(arquivo)){     //While que confere at� o final do arquivo.
        fgets(est.nome_estado, sizeof(ESTADO), arquivo);        //A cada linha o comando fgets vai pegar o estado e a cidade e checar se coincidem com o que o usuario quer registrar.
        if(strcmp(est.nome_estado, estado_pesquisa) == 0){
            contador++;
            fgets(city.nome_cidade, sizeof(CIDADE), arquivo);
            printf("Estado: %sCidade: %s", est.nome_estado, city.nome_cidade);                        //Formato que � visto pelo usu�rio a cada registro que confere ao estado.
            fgets(pes.nome_pessoa, sizeof(PESSOA), arquivo);
            printf("Nome: %s", pes.nome_pessoa);
            fscanf(arquivo, "%2d/%2d/%4d-%c", &pes.dia, &pes.mes, &pes.ano, &pes.sexo);
            printf("Data de nascimento: %d/%d/%d Sexo: %c\n", pes.dia, pes.mes, pes.ano, pes.sexo);
            printf("------------------------------------------------------------------\n\n");
        }
    }
    printf("Pessoas cadastradas na cidade: %d\n", contador);
    if (contador == 0){
        printf("Nenhuma pessoa foi cadastrada no estado digitado.\n\n");
    }
    fclose(arquivo);

    printf("Deseja fazer outra pesquisa? S/N\n");       //Op��o para repetir a fun��o
    fflush(stdin);                                      //� lido uma variavel cmd_repeat, que se for igual a letra em quest�o volta ao �nicio da fun��o
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'S'){
        listar_estado();
    }   else {
        main();
    }
}

void listar_cidade(){                                       //Fun��o parecida � listar_estado, que lista as pessoas cadastradas em uma cidade, de um estado especifico, ambos recebidos pelo usu�rio.
    char cmd_repeat, estado_pesquisa[tamanho], cidade_pesquisa[tamanho];      //Vari�vel de repeti��o da fun��o, e o estado em que se encontra a cidade, e a cidade.
    int contador = 0;                                                         //Vari�vel de contador para pessoas que batem nos requisitos.
    PESSOA pes;
    ESTADO est;
    CIDADE city;

    FILE* arquivo;
    arquivo = fopen("lista_pessoas.txt", "r");      //Arquivo em que foi registrado as pessoas.

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de estados
        fflush(stdin);
        getchar();
        main();
    }

    cabecalho();
    printf("Digite o nome do estado em que se encontr a cidade: ");       //Leitura do estado.
    fflush(stdin);
    fgets(estado_pesquisa, tamanho, stdin);
    strupr(estado_pesquisa);                                    //linha que tranforma tudo em ma�usculo.
                                                                //Essa linha foi repetida em todas as strings registradas, assim � irrelevante o usuario digitar em mai�sculas ou min�sculas.
    printf("\nAgora digite a cidade que ser� pesquisada: ");
    fflush(stdin);                                               //Leitura da cidade a ser pesquisado.
    fgets(cidade_pesquisa, tamanho, stdin);
    strupr(cidade_pesquisa);

    printf("\nAs pessoas que foram cadastradas nesta cidade foram:\n");
    printf("------------------------------------------------------------------\n");

    while (!feof(arquivo)){                                     //While que confere at� o final do arquivo.
        fgets(est.nome_estado, sizeof(ESTADO), arquivo);        //A cada linha o comando fgets vai pegar o estado e a cidade e checar se coincidem com o que o usuario quer registrar.
        if(strcmp(est.nome_estado, estado_pesquisa) == 0){      //Caso os estados forem iguais (O digitado e o registrado)
            fgets(city.nome_cidade, sizeof(CIDADE), arquivo);
            if(strcmp(city.nome_cidade, cidade_pesquisa) == 0){ //Caso a cidade tamb�m for igual.
                contador++;
                printf("Estado: %sCidade: %s", est.nome_estado, city.nome_cidade);
                fgets(pes.nome_pessoa, sizeof(PESSOA), arquivo);
                printf("Nome: %s", pes.nome_pessoa);
                fscanf(arquivo, "%2d/%2d/%4d-%c", &pes.dia, &pes.mes, &pes.ano, &pes.sexo);                             //O formato em que vai aparecer na tela do usu�rio.
                printf("Data de nascimento: %d/%d/%d Sexo: %c\n", pes.dia, pes.mes, pes.ano, pes.sexo);
                printf("------------------------------------------------------------------\n\n");
            }

        }
    }
    printf("Pessoas cadastradas na cidade: %d\n", contador);
    if (contador == 0){
        printf("Nenhuma pessoa foi cadastrada na cidade digitada.\n\n");
    }
    fclose(arquivo);

    printf("Deseja fazer outra pesquisa? S/N\n");       //Op��o para repetir a fun��o
    fflush(stdin);                                      //� lido uma variavel cmd_repeat, que se for igual a letra em quest�o volta ao �nicio da fun��o
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'S'){
        listar_cidade();
    }   else {
        main();
    }
}

void listar_nome(){                                         //Fun��o que faz uma pesquisa no arquivo de pessoas, com nome ou partes do nome, digitadas pelo usu�rio, e os lista.
    FILE* arquivo;
    arquivo = fopen("lista_pessoas.txt", "r");      //Arquivo em que foi registrado as pessoas.

    PESSOA pes;                                     //Structs usadas para o registro de pessoas.
    ESTADO est;
    CIDADE city;
    char cmd_repeat, nome_user[tamanho];                                //Vari�vel para o comando de repeti��o, e o nome a ser pesquisado gerado pelo usu�rio.
    int contador = 0;                                              //Var�avel contador para o n�mero de resultados exibidos na tela.
    int debuffer;                                               //Vari�vel usada para resetar o buffer.
    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de pessoas
        fflush(stdin);
        getchar();
        main();
    }
    cabecalho();
    printf("Digite o nome que ser� pesquisado: ");
    fflush(stdin);
    fgets(nome_user, tamanho, stdin);
    strupr(nome_user);


    while (!feof(arquivo)){
        fgets(est.nome_estado, sizeof(ESTADO), arquivo);            //Primeiro � pego o estado com a fun��o gets, depois com a fun��o fscanf as demais.
        fscanf(arquivo, "%s", &city.nome_cidade);
        fscanf(arquivo, "%s", &pes.nome_pessoa);
        fscanf(arquivo, "%d/%d/%d-%c", &pes.dia, &pes.mes, &pes.ano, &pes.sexo);
        fscanf(arquivo, "%d", &debuffer);                           //Por fim � usado um outro fscanf pra resetar o buffer, tive problemas usando o fflush e essa foi a alternativa que eu encontrei.
        if (compara_nome(nome_user, pes.nome_pessoa) == 1){                               //Caso o nome digitado bater com algum registrado, todas as informa��es s�o exibidas na tela.
            contador++;                                                                   //O contador sobe em 1 para cada vez que um registro bater com o nome digitado.
            printf("\nEstado: %sCidade: %s\n", est.nome_estado, city.nome_cidade);
            printf("Nome: %s\n", pes.nome_pessoa);
            printf("Data de nascimento: %d/%d/%d Sexo: %c\n", pes.dia, pes.mes, pes.ano, pes.sexo);
            printf("------------------------------------------------------------------\n");
        }
    }
    printf("Pessoas que coincidem com o nome digitado: %d\n", contador);
    if (contador == 0){
        printf("Nenhum resultado foi encontrado.\n\n");
    }

    fclose(arquivo);

    printf("Deseja fazer outra pesquisa? S/N\n");       //Op��o para repetir a fun��o
    fflush(stdin);                                      //� lido uma variavel cmd_repeat, que se for igual a letra em quest�o volta ao �nicio da fun��o
    cmd_repeat = getchar();
    cmd_repeat = toupper(cmd_repeat);

    if (cmd_repeat == 'S'){
        listar_nome();
    }   else {
        main();
    }
}

int compara_nome(char nome_user[], char nome_registro[]){   //Fun��o auxiliar para a fun��o listar nome, e compara o nome digitado pelo usu�rio com o j� registrado, retorna 1 se houver coincidencia.
    int checkin;                                            //A vari�vel checkin � o retorno do reultado em 1/0.
    char *ponteiro;        //A fun��o strstr() leva o ponteiro ao primeiro match das 2 strings
    nome_user[strlen(nome_user) - 1] = nome_user[strlen(nome_user)];        //Essa linha retira o ultimo caractere da string, no caso o caractere nulo.

    ponteiro = strstr(nome_registro, nome_user);       //fun��o que mostra se existe equivalente nas 2 strings
    if(ponteiro){                                      //se existir um ponteiro, o checkin se torna positivo.
        checkin = 1;
    } else {
        checkin = 0;
    }
    return checkin;
}

void relatorio_demografico(){                               //Fun��o que gera o relat�rio demogr�fico, � feito a partir de um ano digitado pelo usu�rio, e mostra a porcentagem de registros em cada idade e sexo.
	FILE* arquivo;
    arquivo = fopen("lista_pessoas.txt", "r");      //Arquivo em que s�o registradas as pessoas

    PESSOA pes;                                     //Structs usadas para o registro de pessoas.
    ESTADO est;
    CIDADE city;

    int contador = 0;               //Os contadores usados na fun��o contador � o de pessoas que foram usadas na contagem.
    int ano_atual;                  //O ano digitado pelo usu�rio antes do relat�rio, e usado no calculo de idade.
    int buffer_debugger;            //Esta � a variavel usada para resetar o buffer.
    float percentual_0_5 = 0;                       //Os demais s�o acrescentados a cada pessoa que tem a idade indicada.
    float percentual_6_10 = 0;
    float percentual_11_20 = 0;
    float percentual_21_40 = 0;
    float percentual_41_60 = 0;
    float percentual_acima60 = 0;
    float percentual_masculino = 0;
    float percentual_feminino = 0;
    float percentual_outro = 0;

    if (arquivo == NULL) {
        printf("\nErro ao executar o arquivo...\nPressione Qualquer tecla para continuar...\n");        //Mensagem de erro, para executar o arquivo de pessoas
        fflush(stdin);
        getchar();
        main();
    } else{
        printf("Digite o ano atual: ");             //Seria mais pr�tico se fosse pedido a idade da pessoa no cadastro.
        fflush(stdin);
        fscanf(stdin, "%d", &ano_atual);           //Caso o usu�rio digitar um ano errado os dados de idade tamb�m estar�o errados, mas poder� ser gerado novamente a qualquer momento.
        printf("\nO relat�rio demogr�fico ser� gerado a partir do ano digitado.\nE n�o leva em considera��o dia ou m�s de nascimento, apenas ano.\nAperte qualquer tecla para continuar...");
        fflush(stdin);
        getchar();
        while (!feof(arquivo)){
            fgets(est.nome_estado, sizeof(ESTADO), arquivo);
            fscanf(arquivo, "%s", &city.nome_cidade);
            fscanf(arquivo, "%s", &pes.nome_pessoa);
            fscanf(arquivo, "%2d/%2d/%4d-%c", &pes.dia, &pes.mes, &pes.ano, &pes.sexo);
            fscanf(arquivo, "%d", &buffer_debugger);                 //Essa linha serve para resetar o buffer.
            if (ano_atual - pes.ano >= 0 && ano_atual - pes.ano <= 5){      //Contador para pessoas entre 0 e 5 anos.
                percentual_0_5++;
            }
            if (ano_atual - pes.ano >= 6 && ano_atual - pes.ano <= 10){     //Contador para pessoas entre 6 e 10 anos.
                percentual_6_10++;
            }
            if (ano_atual - pes.ano >= 11 && ano_atual - pes.ano <= 20){    //Contador para pessoas entre 11 e 20 anos.
                percentual_11_20++;
            }
            if (ano_atual - pes.ano >= 21 && ano_atual - pes.ano <= 40){    //Contador para pessoas entre 21 e 40 anos.
                percentual_21_40++;
            }
            if (ano_atual - pes.ano >= 41 && ano_atual - pes.ano <= 60){    //Contador para pessoas entre 41 e 60 anos.
                percentual_41_60++;
            }
            if (ano_atual - pes.ano >= 60){                                 //Contador para pessoas acima de 60 anos.
                percentual_acima60++;
            }
            if (pes.sexo == 'M'){                                           //Contador para pessoas do sexo masculino. O contador geral foi inserido nos sexos para evitar contagens extras.
                percentual_masculino++;
                contador++;
            }
            if (pes.sexo == 'F'){                                           //Contador para pessoas do sexo feminino.
                percentual_feminino++;
                contador++;
            }
            if (pes.sexo == 'O'){                                           //Contador pro sexo que sobrou.
                    percentual_outro++;
                    contador++;
            }
        }

        cabecalho();
        printf("Relat�rio demogr�fico gerado com sucesso!\n\n");
        printf("Porcentagem de pessoas com idade de 0 a 5 anos: %.0f%%\n", (percentual_0_5/contador) * 100);        //Como o relat�rio � mostrado ao usu�rio.
        printf("Porcentagem de pessoas com idade de 6 a 10 anos: %.0f%%\n", (percentual_6_10/contador) * 100);
        printf("Porcentagem de pessoas com idade de 11 a 20 anos: %.0f%%\n", (percentual_11_20/contador) * 100);
        printf("Porcentagem de pessoas com idade de 21 a 40 anos: %.0f%%\n", (percentual_21_40/contador) * 100);
        printf("Porcentagem de pessoas com idade de 41 a 60 anos: %.0f%%\n", (percentual_41_60/contador) * 100);
        printf("Porcentagem de pessoas com idade acima de 60 anos: %.0f%%\n", (percentual_acima60/contador) * 100);
        printf("Porcentagem de pessoas do sexo Masculino: %.0f%%\n", (percentual_masculino/contador) * 100);
        printf("Porcentagem de pessoas do sexo Feminino: %.0f%%\n", (percentual_feminino/contador) * 100);
        printf("Porcentagem de pessoas que digitaram 'O': %.0f%%\n", (percentual_outro/contador) * 100);
        printf("N�mero de pessoas registradas: %d\n", contador);                                                    //N�o necess�rio, mas assim como o relat�rio de erro do arquivo facilita identificar problemas.
    }

    fclose(arquivo);

    printf("\nPressione qualquer tecla para retornar ao menu...\n");                 //Final da fun��o.
    fflush(stdin);
    getchar();                                                                  //getchar() � usado para congelar a tela at� o usu�rio querer retornar ao menu.
    main();
}
