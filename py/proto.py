from sys import argv
gui = not "blind" in argv
if gui:
	import pygame
import libant

SCREEN_SIZE = 700
STAGE_SIZE = 175  # 175 is largest size without bezels for 700 x 700 window
DIRECTIONS = [(0, -1), (1, 0), (0, 1), (-1, 0)]


def draw_bordered_square(x, y, filled, size):
	if gui:
		pygame.draw.rect(screen, (0, 0, 0), (x, y, size, size)), filled
		if not filled:
			pygame.draw.rect(screen, (255, 255, 255), (x + 1, y + 1, size - 2, size - 2))


def grid_to_screen(x, y):
	return x * sizeof_rect + bezel, y * sizeof_rect + bezel

	
def get_or_new(x, y):
	print("here")
	cell = cells.get(x, y)
	if cell is None:
		cell = quadtree.Node(x, y)
		cell.value = False
		cells.insert(cell)
	return cell


def rotate_ant(color, ant):
	# False is right turn
	# True is left turn
	return (ant.orientation + (1 if color else -1)) % 4

if gui:
	pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
	pygame.display.set_caption("Langton's Ant Demo")
	pygame.init()

	screen = pygame.display.get_surface()

sizeof_rect = int(SCREEN_SIZE / STAGE_SIZE)
bezel = int((SCREEN_SIZE - (STAGE_SIZE * sizeof_rect)) / 2)
cells = libant.CartesianGrid()
for x in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
	for y in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
		draw_bordered_square(x, y, False, sizeof_rect)

x_pos = y_pos = int(STAGE_SIZE / 2)
cells.insert(x_pos, y_pos, True)
ant = libant.LangtonsAnt()
ant.position = (x_pos, y_pos)
cells.add_ant(ant)

pause = gui
if not pause:
	input("Press enter to start simulation")
while True:
	if gui:
		for event in pygame.event.get():
			if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
				pause = not pause
			if event.type == pygame.MOUSEBUTTONDOWN:
				x, y = pygame.mouse.get_pos()
				x = int(x / int(SCREEN_SIZE / STAGE_SIZE))
				y = int(y / int(SCREEN_SIZE / STAGE_SIZE))
				flip_cell(cells.get(*grid_to_screen(x, y)))
				print(x, y)
			if event.type == pygame.QUIT:
				exit(0)
	if not pause:
		cell_value = cells.get(ant.x, ant.y)
		draw_bordered_square(*grid_to_screen(ant.x, ant.y), not cell_value, sizeof_rect)
		cells.tick()
		ant.x %= STAGE_SIZE 
		ant.y %= STAGE_SIZE
		if gui:
			pygame.draw.rect(screen, (255, 0, 0), (*map(lambda i: i, grid_to_screen(ant.x, ant.y)), sizeof_rect - 1, sizeof_rect - 1))
	if gui:
		pygame.display.flip()
