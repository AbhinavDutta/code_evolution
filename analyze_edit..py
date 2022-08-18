import os 
dict = {}   #maps node to list of edit actions
class node:
    def __init__(self):
        self.label = ""         #label of the AST node
        self.value = ""         #value of the AST node (if its a leaf) else default
        self.parent = node()    #obvious 
        self.children = []      #ordered list of children . for eg . children[1] => first child
        self.range = (-1,-1)    #i guess its the span of the node 
        self.poswrtpar = -1     #if not root what is child number 
        self.path_to_root = []  #obvious
        self.signature = -1     #id of the AST node

    def __hash__(self):
        return hash((self.label, self.value, self.parent,self.parents,self.range[0],self.range[1],self.poswrtpar,self.path_to_root))
     

class edit_action:
    def _init_(self):
        self.type = ""              #insert delete move
        
        self.insertnode = node()    #
        self.deletenode = node()
        self.movetree = []
        self.movefrom = node()
        self.moveto = node()
        self.movetopos = -1
        self.useful = -1            #is the action useful ?
        self.initVersion = -1
        self.span = {}              #set of nodes

def hash(n):
    



def parseEditActions(editActions[],editScriptfile):
    fullES = editScriptfile.read()
    bulkActions = fullES.split('===')
    for actions in bulkActions:
        action_ = actions.split('---')
        if(action_[0] == 'match'):
            continue
        if(action_[0] == 'insert-node'):
            
        if(action_[0] == 'insert-tree'):
            breakIntoAtoms(editActions,action_[0])
        
        if(action_[0] == 'delete-node'):

        if(action_[0] == 'delete-tree'):
            breakIntoAtoms(editActions,action_[0])

        if(action_[0] == 'move-tree'):
            breakIntoAtoms(editActions,action_[0])


def parseAST(astNodes[],astfile):
    fullAst = astfile.read()
    lines = fullAst.split('\n')
    parents = []
    
    for leaf in lines:
        space = 0
        zone = 0 # 0 -> leading spaces , 1-> label name, 2 -> value , 3-> range
        potential_par = set(<iter>) #list of potential parents
        for i in range(0,len(leaf)):
            if (zone==0 and c==' '):
                space=space+1
                zone=zone+1
            else if (zone==0 and c != ' '): #start labelname
                readL

            else if (zone==1):
                if(c==':'): #leading to value zone
                    zone++
                if(c==' '): #leading to range zone
                    zone+=2


        curr = node()
        curr.label = extract_
        curr.value = 
        curr.parent = 
        curr.parent.children.append
        curr.range = 

        astNodes.append(curr)








token = "SGX1SBMEGUUY"
exercise = "gcd"

    
