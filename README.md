# Inertial Navigator
Um sistema para traçar trajetórias com base numa MPU (Motion Process Unity)

Este projeto foi baseado em conversas que tive com o amigo Jonatan. A versão dele pode ser encontrada no seguinte repositório:

https://github.com/Jhonatan-Brandel/MPU9250-Inertial-Navigation-Device

Trata-se, como o nome diz, de um navegador inercial. Basicamente o sistema possui uma bússola e um contador de passos. A cada passo é computada uma distância percorrida na direção daquele passo, o que permite traçar a trajetória de um indivíduo caminhando normalmente.

Como diferenças entre as duas implementações, ele criou um dispositivo para coletar os dados. Esta minha versão se utiliza dos sensores presentes em um smartphone ordinário. Em um nível mais técnico, a minha versão não se utiliza de giroscópios, calculando a direção através do magnetômetro.

Para fugir do java e poder agilizar o processo, os programas que rodam no telefone foram escritos em C, compilados através do Android NDK e rodados com o ADB. O método não é muito intuitivo, mas qualquer um familiarizado com um terminal de comando conseguirá executar o processo. O arquivo "Computer-Side/script.bat" é um exemplo de procedimento.


![alt text](https://raw.githubusercontent.com/Pusiol/Inertial-Navigator/master/20190125_121227.jpg)


Na imagem acima apresentamos o set-up de calibração, linhas retas defasadas em 30º. O celular é colocado em cada linha e a leitura é feita através do programa no arquivo "Device-Side/medsens.c". O comando "adb shell /data/local/tmp/medsens >> nome_qualquer" pode ser usado para salvar automaticamente cada leitura no arquivo "nome_qualquer".




![alt text](https://raw.githubusercontent.com/Pusiol/Inertial-Navigator/master/lcm.png)


O círculo em verde é o que se obtém de leitura do magnetômetro. A figura pode ser gerada fornecendo um arquivo de calibração ao programa "Computer-Side/cal.py". Percebe-se que há um offset no campo, gerado pelo magnetismo do próprio telefone. Para ser possível a medição de ângulo esse offset deverá ser removido. Constatamos que o campo varia com o lugar, mas sobretudo com o celular utilizado.

Após obtido o arquivo de calibração o dispositivo está pronto. Foram escritas duas versões, uma em tempo real e a outra não.

Para a versão em tempo real, o celular e o computador devem estar na mesma rede. Recomendamos gerar a rede pelo celular. Rode o programa "Device-Side/rede3-detect.c" no dispositivo e depois o programa "Computer-Side/ss3.py" depois de introduzir o ip correto do celular. Se tudo correr bem o programa deve começar a plotar a trajetória em tempo real.

No caso offline o celular pode ser usado para gerar dados que depois podem ser importados para o computador. Para isso deve ser rodado o programa "Device-Side/rede3-detect-ofline.c" com a flag "nohup", para a execução não ser interrompida quando o celular sair da rede. O programa não tem interface de usuário, então para interromper a gravação a flag é uma gravidade negativa, que pode ser obtida criando um dispositivo antigravidade ou virando o celular de cabeça pra baixo.

Depois de feita a leitura e encerrado o programa, o arquivo dat gerado na pasta do programa executado deve ser copiado para a pasta do programa "Computer-Side/ss3-ofline.py". Este programa irá plotar a trajetória.

Abaixo um teste, conduzido nos arredores da minha casa.


![alt text](https://raw.githubusercontent.com/Pusiol/Inertial-Navigator/master/ttt.jpg)


Meu trajeto foi sair, ir à praça, dar duas voltas, voltar pela rua de baixo e passar por trás do quarteirão. O sistema não é perfeito, mas consegue algum resultado. Pensando agora, eu estava com um pequeno íma no outro bolso, talvez tenha sido o responsável pelo desvio. Vou repetir o teste qualquer dia.
