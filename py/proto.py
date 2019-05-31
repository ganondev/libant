import pygame
import libant

SCREEN_SIZE = 700
STAGE_SIZE = 175  # 175 is largest size without bezels for 700 x 700 window
DIRECTIONS = [(0, -1), (1, 0), (0, 1), (-1, 0)]


def draw_bordered_square(x, y, filled, size):
	cells[(x, y)] = pygame.draw.rect(screen, (0, 0, 0), (x, y, size, size)), filled
	if not filled:
		pygame.draw.rect(screen, (255, 255, 255), (x + 1, y + 1, size - 2, size - 2))


def grid_to_screen(x, y):
	return x * sizeof_rect + bezel, y * sizeof_rect + bezel


def flip_cell(cell):
	draw_bordered_square(cell[0].x, cell[0].y, not cell[1], sizeof_rect)


def rotate_ant(color, ant):
	# False is right turn
	# True is left turn
	return (ant.orientation + (1 if color else -1)) % 4


pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
pygame.display.set_caption("Langton's Ant Demo")
pygame.init()

screen = pygame.display.get_surface()

sizeof_rect = int(SCREEN_SIZE / STAGE_SIZE)
bezel = int((SCREEN_SIZE - (STAGE_SIZE * sizeof_rect)) / 2)
cells = {}
for x in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
	for y in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
		draw_bordered_square(x, y, False, sizeof_rect)

x_pos = y_pos = int(STAGE_SIZE / 2)
cell = cells[grid_to_screen(x_pos, y_pos)]
flip_cell(cell)
ant = libant.LangtonsAnt()
ant.position = (x_pos, y_pos)

pause = True
while True:
	for event in pygame.event.get():
		if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
			pause = not pause
		if event.type == pygame.MOUSEBUTTONDOWN:
			x, y = pygame.mouse.get_pos()
			x = int(x / int(SCREEN_SIZE / STAGE_SIZE))
			y = int(y / int(SCREEN_SIZE / STAGE_SIZE))
			flip_cell(cells[grid_to_screen(x, y)])
			print(x, y)
		if event.type == pygame.QUIT:
			exit(0)
	if not pause:
		cell = cells[grid_to_screen(*ant.position)]
		new_angle = rotate_ant(cell[1], ant)
		flip_cell(cell)
		ant.orientation = new_angle
		ant.directive(ant)
		ant.x %= STAGE_SIZE 
		ant.y %= STAGE_SIZE
		pygame.draw.rect(screen, (255, 0, 0), cells[grid_to_screen(ant.x, ant.y)][0])
	pygame.display.flip()
