import discord
import ManejoComandos
from tokenn import token
import datetime

intents = discord.Intents.default()
intents.message_content = True
client = discord.Client(intents=intents)


@client.event
async def on_ready():
    print(f'We have logged in as {client.user}')


@client.event
async def on_message(message):
    import time
    if message.author == client.user:
        return
    if message.content.startswith('Ñ'):
        for i in range(10): 
            time.sleep (1)
            await message.channel.send("Ñ")
    if 'resultado' in message.content.lower():
        await message.channel.send('^^')
        ManejoComandos.imprimir(message)
    else: await message.channel.send(ManejoComandos.elegirComando(message))

client.run(token)