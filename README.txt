Natal, 06/Outubro/2015

# Identificação #
	
	* Instituição: Universidade Federal do Rio Grande do Norte (UFRN)
	* Disciplina:  Estrutura de Dados Básicos I (IMD0029)

	* Aluno:       Vinícius Campos Tinoco Ribeiro
	* Matrícula:   2014025284

	* Aluno:       Vitor Rodrigues Greati
	* Matrícula:   2015034967

# Introdução #

O projeto consiste no desenvolvimento de um BARES (Basic ARithmetic Expression
Evaluator based on Stacks), que significa Avaliador de Expressões Aritiméticas 
Básicas baseado em Pilhas. A tarefa consiste em ler expressões (strings), realizar
o possível cálculo e se a expressão estiver correta, deve-se retornar o valor da expressão, 
senão os erros da expressão.

# Operações Permitidas #

	* - (Unário) : Negação do operando
	* + (Binário): Adição entre dois operandos
	* - (Binário): Subtração entre dois operandos
	* * (Binário): Multiplicação entre dois operandos
	* / (Binário): Divisão entre dois operandos
	* % (Binário): Módulo entre dois operandos
	* ^ (Binário): Potência entre dois operandos (base e expoente)

# Outros operadores #
	
	* ( : Quebra precedência
	* ) : Quebra precedência 

# Erros detectáveis #

	1 Constante numérica inválida: Algum dos operandos da expressão está 
	fora do intervalo permitido (-32.767 a 32.767)
	2 Falta de operando: Falta de algum operando para utilizar um operador
	3 Operando inválido: Operando não permitido, algum digito diferente de (0 1 2 3 4 5 6 7 8 9)
	4 Operador inválido: Operador não permitido, operador diferente de ( ( ) - + * / % ^)
	5 Falta operador: Falta algum operador entre operandos
	6 Fechamento de escopo inválido: Fechamento de escopo sem abertura
	7 Escopo aberto: Escopo sem fechamento
	8 Divisão por zero: Quando é realizado uma operãção de divisão e o denominador é 0. 

# Estrutura #

O projeto está sub-dividido em 6 pastas:
	
	* bin: Possui os executáveis do projeto
	* data: Possui arquivos que servem como entrada e saida para a execução do programa
	* documentation: Possui toda a documentação do projeto com doxygen
	* include: Possui o arquivo de cabeçalho das classes do projeto
	* lib: Possui os objetos do sistema
	* src: Possui o arquivo de implementação dos métodos das classes do projeto

# Guia de utilização(MODO TEXTO) - Linux #
	
	1 - Descompactar o projeto na pasta de preferência
	1 - Abra o terminal
	2 - make
	3 - Para executar, tem-se quatro maneiras:
		* sem make:  
		./bin/bares data/<arquivo_de_entrada>
		- O comando acima apenas executa o programa com a entrada de arquivos.
		ou 
		./bin/bares /data/<arquivo_de_entrada> data/<arquivo_de_saida>
		- O comando acima apenas executa o programa com a entrada de arquivos e salva na pasta de data

		* com make:
		make run data/<arquivo_de_entrada>
		- O comando acima apenas executa o programa com a entrada de arquivos.
		ou
		make run /data/<arquivo_de_entrada> data/<arquivo_de_saida>
		- O comando acima apenas executa o programa com a entrada de arquivos e salva na pasta de data

		Obs: <arquivo_de_entrada> é um arquivo de texto com entradas das expressões
			 <arquivo_de_saida> será o arquivo que armazenará os resultados das expressões
	4 - Para limpar os arquivos de compilação:
		make clean

# Erros tratados
	* Quando não se informa o arquivo de entrada ou um caminho inválido para ele
	* Quando não se informa um caminho válido para o arquivo de saída

# Resultado no valgrind(MODO TEXTO) #

	* O projeto passou no valgrind sem vazamento de memória,
	resposta no terminal ao fim de uma execução: 

	==5906== 
	==5906== HEAP SUMMARY:
	==5906==     in use at exit: 0 bytes in 0 blocks
	==5906==   total heap usage: 477 allocs, 477 frees, 90,519 bytes allocated
	==5906== 
	==5906== All heap blocks were freed -- no leaks are possible
	==5906== 
	==5906== For counts of detected and suppressed errors, rerun with: -v
	==5906== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)

	* Para fazer o teste basta rodar o comando
	make run_valgrind <arquivo_de_entrada> 
	ou
	make run_valgrind <arquivo_de_entrada> <arquivo_de_saida>
  	
  	Obs: É preciso ter pelo menos rodado o comando make antes de testar o make run_valgrind