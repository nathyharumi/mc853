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
 
## Detalhes de implementação
* ddns/tcp-server.py
  1. Obtém o caminho para a página HTML, que foi passado como parâmetro
      * Se nenhum parâmetro for passado, usa por padrão o caminho `~/public_html/ddns.html`
  2. Abre o servidor TCP e espera uma conexão
  3. Obtém o IP passado pelo cliente
  4. Obtém o data e hora atual
  5. Cria ou edita página HTML usando as informações e configura uma atualização automática da página a cada 5 segundos
* ddns/ddns.ino
  1. Conecção TCP com página [ident.me]
  2. Requisição HTML para a página
  3. Parser da página obtida para obtenção do indereço IP
  4. Coneção com servidor DDNS python
      * Se a conecção falhar 10 vezes, vai para passo 6
  5. Envio do IP obtido pelo python
  6. Deep sleep the 15 minutos
