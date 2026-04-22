import socket
import pygame
import sys

# --- Network Setup ---
TCP_IP = '192.168.4.1'
TCP_PORT = 80

try:
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect((TCP_IP, TCP_PORT))
    print(f"Connected to {TCP_IP}")
except Exception as e:
    print(f"Connection failed: {e}")
    sys.exit()

# --- Pygame Setup ---
pygame.init()
pygame.display.set_mode((200, 200))
pygame.display.set_caption("Robot Controller")
clock = pygame.time.Clock()

# --- Joystick Setup ---
pygame.joystick.init()
joystick = None
if pygame.joystick.get_count() > 0:
    joystick = pygame.joystick.Joystick(0)
    joystick.init()
    print("Controller connected:", joystick.get_name())

# --- State Variables ---
last_cmd = ""  # Track last sent command to prevent spamming

def send_command(cmd):
    """Sends command only if it's different from the last one."""
    global last_cmd
    if cmd != last_cmd:
        try:
            client.send(cmd.encode())
            print(f"Sent: {cmd}")
            last_cmd = cmd
        except Exception as e:
            print(f"Send error: {e}")

running = True
while running:
    # 1. Process Events (Keyboard & Buttons)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        
        # Action Buttons (Z, X, C, V or Joystick Buttons)
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_z: send_command('1B')
            if event.key == pygame.K_x: send_command('2B')
            if event.key == pygame.K_c: send_command('3B')
            if event.key == pygame.K_v: send_command('4B')
        
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == 0: send_command('1B')
            if event.button == 1: send_command('2B')
            if event.button == 2: send_command('3B')
            if event.button == 3: send_command('4B')

    # 2. Process Directional Input (Continuous States)
    keys = pygame.key.get_pressed()
    
    # Initialize directions
    forward = keys[pygame.K_UP]
    backward = keys[pygame.K_DOWN]
    left = keys[pygame.K_LEFT]
    right = keys[pygame.K_RIGHT]

    # Overlay Joystick Analog Input
    if joystick:
        deadzone = 0.3
        y_axis = joystick.get_axis(1) # Vertical
        x_axis = joystick.get_axis(0) # Horizontal
        
        if y_axis < -deadzone: forward = True
        if y_axis > deadzone:  backward = True
        if x_axis < -deadzone: left = True
        if x_axis > deadzone:  right = True

    # 3. Determine Movement Command
    current_move = '0' # Default Stop
    if forward:    current_move = '1'
    elif backward: current_move = '2'
    elif left:     current_move = '4'
    elif right:    current_move = '3'

    # 4. Send Movement (If changed)
    send_command(current_move)

    # 5. Cap the frame rate to 30 FPS (Prevents CPU maxing out)
    clock.tick(30)

client.close()
pygame.quit()
