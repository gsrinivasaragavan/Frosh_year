# time complexity: O(n^2)
# space complexity: O(n) 
''' 
This function will determine if there is a loop in a linked list.
We have two classes, a Node class and a List class. THe Node class
creates the Nodes that will end up in the linked list. The list 
class adds nodes to the linked list and also checks if a loop is
present in the linked list.  
'''
class Node:
	def __init__(self, data, nextone = None):
		self.data = data
		self.nextone = nextone

class List:
	def __init__(self):
		self.head = None
	def add_node(self, node):
		if self.head:
			current = self.head #python recognizes head to be a Node
			while current.nextone != None:
				current = current.nextone #current becomes next one as 
				#long as next is not null
			current.nextone = node
		else:
			self.head = node
	def loop_check(self):
		previous = []
		current = self.head
		while current != None:
			if current in previous: #node objects stored in list notdata
				return False #checks if the current node has already been a node
			previous.append(current) #if not, appends it to previous list
			current = current.nextone #set current to the next one 
		return True
		
list1 = List()	
Node1 = Node(1, None)
Node2 = Node(2, None)
Node3 = Node(3, None)
Node4 = Node(4, Node1)
list1.add_node(Node1)
list1.add_node(Node2)
list1.add_node(Node3)
list1.add_node(Node4)

print(list1.loop_check())



			
	
