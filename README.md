# Dynamic DNS

## Modo de uso
* Inicializar servidor python
  * Conectar ao servidor Xaveco do IC
  * Ir para raiz da pasta do projeto
  * Rodar servidor
    * `python3 ddns/tcp-server.py [<caminho para página html>]`
    * Obs: Por padrão o servidor criará um arquivo HTML em `~/public_html/ddns.html`
* Carregar o programa `ddns/ddns.ino` na placa ESP8266
  * Após carregar o programa, ativar o deep sleep conectando um fio entre a porta RST e D0 do ESP8266
* Entrar na página
  * Se você utilizou o caminho padrão, o link será http<span><span>://students.ic.unicamp.br/~<USUÁRIO IC>/ddns.html
