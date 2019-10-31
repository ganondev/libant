import pygame
import libant
import itertools
from random import randint
from time import sleep
import data

SCREEN_SIZE = 700
STAGE_SIZE = 175  # 175 is largest size without bezels for 700 x 700 window
sizeof_rect = int(SCREEN_SIZE / STAGE_SIZE)
bezel = int((SCREEN_SIZE - (STAGE_SIZE * sizeof_rect)) / 2)

def draw_bordered_square(x, y, filled, size):
	pygame.draw.rect(screen, (0, 0, 0), (x, y, size, size)), filled
	if not filled:
		pygame.draw.rect(screen, (255, 255, 255), (x + 1, y + 1, size - 2, size - 2))


def grid_to_screen(x, y):
	return x * sizeof_rect + bezel, y * sizeof_rect + bezel

def screen_to_grid(x, y):
	return int((x - bezel) / sizeof_rect), int((y - bezel) / sizeof_rect)

	
def flip_cell(x, y):
	cells[(x, y)] = not cells[(x, y)]
	draw_bordered_square(*grid_to_screen(x, y), cells[(x, y)], sizeof_rect)


def draw_cells():

	for x in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
		for y in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
			coord = screen_to_grid(x, y)
			value = coord in cells and cells[coord]
			draw_bordered_square(x, y, value, sizeof_rect)

def neighbours_of(x, y):
	
	for d in directions:
		try:
			yield ((x + d[0]) % STAGE_SIZE, (y + d[1]) % STAGE_SIZE)
		except:
			pass

def insert(collection, location):
	
	collection[location] = True
	for n in neighbours_of(*location):
		if not (n in collection):
			collection[n] = False

directions = []

for x in [-1, 0, 1]:
	for y in [-1, 0, 1]:
		directions.append((x, y))

directions.remove((0,0))

pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
pygame.display.set_caption("Game of Life Redux")
pygame.init()

screen = pygame.display.get_surface()

cells = { }
# for pair in itertools.product([ z for z in range(STAGE_SIZE)], [ z for z in range(STAGE_SIZE)]):
	# v = randint(0, 1)
	# if v:
		# insert(cells, pair)
		
for x in range(len(data.grid)):
	for y in range(len(data.grid[x])):
		if data.grid[x][y]:
			insert(cells, (x, y))
draw_cells()

pause = True
round = 0
while True:
	for event in pygame.event.get():
		if event.type == pygame.KEYDOWN and event.key == pygame.K_SPACE:
			pause = not pause
		if event.type == pygame.MOUSEBUTTONDOWN:
			x, y = pygame.mouse.get_pos()
			x = int(x / int(SCREEN_SIZE / STAGE_SIZE))
			y = int(y / int(SCREEN_SIZE / STAGE_SIZE))
			flip_cell(x, y)
			print(x, y)
		if event.type == pygame.QUIT:
			exit(0)
	if not pause and round < 50:
		new_cells = {}
		for cell in cells:
			neighbours = len(list(filter(lambda n: (n in cells) and cells[n], neighbours_of(*cell))))
			if (cells[cell] and neighbours in [2, 3]) or neighbours == 3:
				insert(new_cells, cell)
		cells = new_cells
		draw_cells()
		round += 1
	pygame.display.flip()
