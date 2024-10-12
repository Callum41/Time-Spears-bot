import Comandos
import datetime

def elegirComando(text):
    respuesta = ''
    if text.content in Comandos.commands:
        respuesta = Comandos.commands[text.content]
    return respuesta
def imprimir(message):
    jugadores = []
    marcador = ''
    texto = message.content
    lista = texto.split(' ')
    for i in lista:
        if i.startswith('<'):
            jugadores.append(i)
        elif i.startswith('('):
            marcador = i
    resultado = open('resultadosPeleas.txt', 'a')
    print(marcador)
    resultado.write('\n' + jugadores[0] + ' ' + marcador+ ' '+ jugadores[1] + '  (' + str(datetime.datetime.now()) + ')')
    resultado.close()
