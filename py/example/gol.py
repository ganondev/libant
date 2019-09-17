import pygame
from random import randint
from time import sleep

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
	cells[x][y] = not cells[x][y]
	draw_bordered_square(*grid_to_screen(x, y), cells[x][y], sizeof_rect)


def draw_cells():

	for x in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
		for y in range(bezel, STAGE_SIZE * sizeof_rect + bezel, sizeof_rect):
			coord = screen_to_grid(x, y)
			draw_bordered_square(x, y, cells[coord[0]][coord[1]], sizeof_rect)

directions = []

for x in [-1, 0, 1]:
	for y in [-1, 0, 1]:
		directions.append((x, y))

directions.remove((0,0))

def get_neighbours(x, y):
	
	total = 0
	for d in directions:
		try:
			if cells[(x + d[0]) % STAGE_SIZE][(y + d[1]) % STAGE_SIZE]:
				total += 1
		except:
			print(x, y, d, (x + d[0]) % SCREEN_SIZE, (y + d[1]) % SCREEN_SIZE)
			raise IndexError
	return total
	

pygame.display.set_mode((SCREEN_SIZE, SCREEN_SIZE))
pygame.display.set_caption("Game of Life Classic Demo")
pygame.init()

screen = pygame.display.get_surface()

cells = [ [ randint(0,1) for y in range(175) ] for x in range(175) ]

pause = True
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
	if not pause:
		new_cells = []
		for x in range(STAGE_SIZE):
			new_row = []
			for y in range(STAGE_SIZE):
				neighbours = get_neighbours(x, y)
				cell = cells[x][y]
				if cell:
					if neighbours < 2 or neighbours > 3:
						cell = 0
				elif neighbours == 3:
					cell = 1
				new_row.append(cell)
			new_cells.append(new_row)
		cells = new_cells
		draw_cells()
	pygame.display.flip()
