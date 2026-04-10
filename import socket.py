import socket
import pygame

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect(('192.168.4.1', 80))

client.send('0'.encode())

pygame.init()
screen = pygame.display.set_mode((100, 100))

running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_UP:
                client.send('1'.encode())
            elif event.key == pygame.K_DOWN:
                client.send('2'.encode())
            elif event.key == pygame.K_LEFT:
                client.send('3'.encode())
            elif event.key == pygame.K_RIGHT:
                client.send('4'.encode())
        elif event.type == pygame.KEYUP:
            client.send('0'.encode())


client.close()
pygame.quit()