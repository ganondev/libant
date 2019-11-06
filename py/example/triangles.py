from sys import argv
from math import ceil
gui = not "blind" in argv
if gui:
	import pygame
import libant

SCREEN_SIZE = 700
STAGE_SIZE_X = 30
STAGE_SIZE_Y = ceil(STAGE_SIZE_X / 2) - 1

orientation = "UP"
allow_point_transition = False

def next_orientation(value, up):
	global orientation
	if (not allow_point_transition) and ((up and orientation == "DOWN") or ((not up) and orientation == "UP")):
		print("UP:", up, "ORIENTATION:", orientation)
		exit(1)
	if up:
		if value:
			if orientation == "UP":
				orientation = "RIGHT"
			elif orientation == "RIGHT":
				orientation = "DOWN"
			elif orientation == "LEFT":
				orientation = "RIGHT"
			elif orientation == "DOWN":
				orientation = "LEFT"
		else:
			if orientation == "UP":
				orientation = "LEFT"
			elif orientation == "RIGHT":
				orientation = "LEFT"
			elif orientation == "LEFT":
				orientation = "DOWN"
			elif orientation == "DOWN":
				orientation = "RIGHT"
	else:
		if value:
			if orientation == "DOWN":
				orientation = "LEFT"
			elif orientation == "RIGHT":
				orientation = "LEFT"
			elif orientation == "LEFT":
				orientation = "UP"
		else:
			if orientation == "DOWN":
				orientation = "RIGHT"
			elif orientation == "RIGHT":
				orientation = "UP"
			elif orientation == "LEFT":
				orientation = "RIGHT"

dirs = {
	"UP": (0, -1),
	"LEFT": (-1, 0),
	"RIGHT": (1, 0),
	"DOWN": (0, 1)
}

def draw_bordered_triangle(x, y, filled, size, color=None):
	if gui:
		up = (x % 2) ^ (y % 2)
		x = x * sizeof_rect / 2
		y = y * sizeof_rect
		vertices = [(x, y), (x + size, y), (x + size / 2, y + size)] \
			if up else [(x, y + size), (x + size, y + size), (x + size / 2, y)]
		pygame.draw.polygon(screen, (255, 255, 255), vertices)
		pygame.draw.polygon(screen, (0, 0, 0), vertices, int(not filled))
		if color:
			pygame.draw.polygon(screen, color, vertices)


def grid_to_screen(x, y):
	return x * sizeof_rect + bezel, y * sizeof_rect + bezel


if gui:
	pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
	pygame.display.set_caption("Langton's Ant Demo")
	pygame.init()

	screen = pygame.display.get_surface()

sizeof_rect = int(SCREEN_SIZE / (STAGE_SIZE_X / 2))
cells = libant.CartesianGrid()
for x in range(STAGE_SIZE_X):
	for y in range(STAGE_SIZE_Y):
		draw_bordered_triangle(x, y, False, sizeof_rect)

x_pos = int(STAGE_SIZE_X / 2)
y_pos = int(STAGE_SIZE_Y / 2)
ant = libant.LangtonsAnt()
ant.position = (x_pos, y_pos)
cells.add_ant(ant)
draw_bordered_triangle(ant.x, ant.y, True, sizeof_rect, (255, 0, 0))

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
				x = int(x / int(SCREEN_SIZE / STAGE_SIZE_X))
				y = int(y / int(SCREEN_SIZE / STAGE_SIZE_X))
				flip_cell(cells.get(*grid_to_screen(x, y)))
				print(x, y)
			if event.type == pygame.QUIT:
				exit(0)
	if not pause:
		up = not (ant.x % 2) ^ (ant.y % 2)
		cell_value = not cells.get(ant.x, ant.y)
		cells.insert(ant.x, ant.y, cell_value)
		next_orientation(cell_value, up)
		draw_bordered_triangle(ant.x, ant.y, cell_value, sizeof_rect)
		direction = dirs[orientation]
		ant.x += direction[0]
		ant.y += direction[1]
		ant.x %= STAGE_SIZE_X 
		ant.y %= STAGE_SIZE_Y
		if gui:
			draw_bordered_triangle(ant.x, ant.y, True, sizeof_rect, (255, 0, 0))
	if gui:
		pygame.display.flip()

# has value turn right