from functools import reduce
 
class Node(object):

	NE = 0
	NW = 1
	SW = 3
	SE = 2
	
	def __init__(self, x, y):
		self.value = None
		self.children = None
		self.x = x
		self.y = y
		self.is_root = False

	@property
	def is_leaf(self):
		return not self.children

	def put_child(self, node, quadrant):
		if not self.is_leaf:
			existing_child = self.children[quadrant]
			if existing_child:
				existing_child.put_child(node, existing_child % node)
			else:
				self.children[quadrant] = node
		else:
			self._split(node, quadrant)

	def _split(self, child, index):
		self.children = [None, None, None, None]
		self.children[index] = child
	
	def __getitem__(self, key):
		if not self.is_leaf:
			return self.children[key]
		else:
			raise ValueError("Node is a leaf -- no children")

	def __eq__(self, other):
		t = type(other)
		if t is tuple:
			x, y = other
		elif t is Node:
			x, y = other.x, other.y
		else:
			raise TypeError("Must compare Node with another Node")
		
		return self.x == x and self.y == y

	def __mod__(self, other):
		# Check quadrant of 'other' compared to self's position
		if self == other:
			return -1
		t = type(other)
		if t is tuple:
			x, y = other
		elif t is Node:
			x, y = other.x, other.y
		else:
			raise TypeError("Must compare Node with another Node")

		vertical = int(self.y > y) * 2
		horizontal = int(self.x > x)

		return vertical | horizontal

	
	def __str__(self):
		return f"Node at ({self.x}, {self.y}). Leaf? {self.is_leaf}{f' Value: {self.value}' if self.is_leaf else ''}"

	def __repr__(self):
		children_string = '\n\t[\n\t\tNE: {},\n\t\tNW: {},\n\t\tSE: {},\n\t\tSW: {}\n\t]'.format(*map(lambda c: f"Node({c.x}, {c.y})" if c else None, self.children)) if self.children else None
		return f"Node({self.x}, {self.y})\n{{\n\tvalue: {self.value},\n\tis_leaf: {self.is_leaf},\n\tis_root: {self.is_root},\n\tself.children: {children_string}\n}}"

class QTree(object):

	# TODO this static method should return the location of the child by reference
	@staticmethod
	def _find(node, x, y) -> Node:
		if type(x) is int and type(y) is int:
			compare = node % (x, y)
			if compare == -1:
				return node
			else:
				if node.is_leaf:
					return None
				return QTree._find(node[compare], x, y)
		else:
			raise TypeError("x and y must be integers")

	def __init__(self):
		self.root = Node(0,0)
		self.root.is_root = True

	def get(self, x, y):
		return QTree._find(self.root, x, y)

	def has_cell(self, x, y):
		return not not self.get(x, y)

	def insert(self, node):
		self.root.put_child(node, self.root % node)


q = QTree()
list(
	map(
		lambda n: q.insert(n), [
			Node(1,0),
			Node(1,2),
			Node(-1,0),
			Node(0,-1),
			Node(6, 1),
			Node(8, 3),
			Node(7, 2)
		]
	)
)
