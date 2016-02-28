'''
Created on 16 Feb 2016

@author: WindyMe
'''
'''
Created on 28 May 2014

@author: windy
'''

def main_as_def():
    
    f = open('KFat64.txt', 'a')
    LS = open('Links64.txt', 'a')
    FI = open('InPaths64.txt', 'a')
    FO = open('OutPaths64.txt', 'a')
    
    NoOfServers = 64
    NoOfPods = 4
    NoOfServersPerToR = 8
    
    MidSwitchesStarts = NoOfServers + 1
    MidSwitchesEnd = MidSwitchesStarts + (NoOfPods * 4) - 1
    EdgeSwitchesStart = MidSwitchesEnd + 1
    EdgeSwitchesEnd = EdgeSwitchesStart + NoOfPods - 1
    TotalNodes = EdgeSwitchesEnd + 1
    ServersStart = 1 
    ServerArrayStart =  ServersStart 
                
    servers = []
    for s in range (1, MidSwitchesStarts):
        servers.append(s)
    
    
    servers1 = []
    for s1 in range (0, NoOfServersPerToR):
        servers1.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
    
    servers2 = []
    for s2 in range (0, NoOfServersPerToR):
        servers2.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers3 = []
    for s3 in range (0, NoOfServersPerToR):
        servers3.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers4 = []
    for s4 in range (0, NoOfServersPerToR):
        servers4.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers5 = []
    for s5 in range (0, NoOfServersPerToR):
        servers5.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers6 = []
    for s6 in range (0, NoOfServersPerToR):
        servers6.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers7 = []
    for s7 in range (0, NoOfServersPerToR):
        servers7.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    servers8 = []
    for s8 in range (0, NoOfServersPerToR):
        servers8.append(ServerArrayStart)
        ServerArrayStart = ServerArrayStart + 1
        
    G=nx.Graph()
    
    for num in range (1, MidSwitchesStarts):
        G.add_node(num)
    
    for num2 in range (MidSwitchesStarts, EdgeSwitchesStart):
        G.add_node(num2)
    
    for num3 in range (EdgeSwitchesStart, TotalNodes):
        G.add_node(num3)
    
    i = MidSwitchesStarts    
    while (i < EdgeSwitchesStart ):
        G.add_edge(i,i+2)
        l1 = str(i) + "-" + str(i+2)
        LS.write(l1)
        LS.write('\n')
        
        l1 = str(i+2) + "-" + str(i)
        LS.write(l1)
        LS.write('\n')
        
        G.add_edge(i,i+3)
        l1 = str(i) + "-" + str(i+3)
        LS.write(l1)
        LS.write('\n')
        
        l1 = str(i+3) + "-" + str(i)
        LS.write(l1)
        LS.write('\n')
        
        h = 0
        while (h < NoOfPods):
            G.add_edge(i,EdgeSwitchesStart + h)
            l1 = str(i) + "-" + str(EdgeSwitchesStart + h)
            LS.write(l1)
            LS.write('\n')
            
            l1 = str(EdgeSwitchesStart + h) + "-" + str(i)
            LS.write(l1)
            LS.write('\n')
            
            h = h + 2
    
        G.add_edge(i+1,i+2)
        l1 = str(i+1) + "-" + str(i+2)
        LS.write(l1)
        LS.write('\n')
        
        l1 = str(i+2) + "-" + str(i+1)
        LS.write(l1)
        LS.write('\n')
        
        G.add_edge(i+1,i+3)
        l1 = str(i+1) + "-" + str(i+3)
        LS.write(l1)
        LS.write('\n')
        
        l1 = str(i+3) + "-" + str(i+1)
        LS.write(l1)
        LS.write('\n')
        
        h2 = 1
        while (h2 < NoOfPods):
            G.add_edge(i+1,EdgeSwitchesStart + h2)
            l1 = str(i+1) + "-" + str(EdgeSwitchesStart + h2) 
            LS.write(l1)
            LS.write('\n')
            
            l1 = str(EdgeSwitchesStart + h2) + "-" + str(i+1)
            LS.write(l1)
            LS.write('\n')
            
            h2 = h2 + 2
        
        for l in range (0, NoOfServersPerToR):
            G.add_edge(i+2,ServersStart)
            l1 = str(i+2) + "-" + str(ServersStart)
            LS.write(l1)
            LS.write('\n')
            
            l1 = str(ServersStart) + "-" + str(i+2)
            LS.write(l1)
            LS.write('\n')
            
            ServersStart = ServersStart + 1
            
        for l in range (0, NoOfServersPerToR):
            G.add_edge(i+3,ServersStart)
            l1 = str(i+3) + "-" + str(ServersStart)
            LS.write(l1)
            LS.write('\n')
            
            l1 = str(ServersStart) + "-" + str(i+3)
            LS.write(l1)
            LS.write('\n')
            
            ServersStart = ServersStart + 1
            
        i = i+4
    
    #nx.write_gml(G,'KFat48.gml')  
    #pos1 = nx.spring_layout(G)
    #nx.draw_networkx(G,pos1)
    #ppt.savefig('KFat48.png')
    #ppt.clf()
    
    Num_Nodes_arr = G.nodes()
    Num_Nodes = len(Num_Nodes_arr)

    for x in range (0,Num_Nodes):
        for y in range (0,Num_Nodes):
            src = Num_Nodes_arr[x]
            dst = Num_Nodes_arr[y]
            if ((src != dst) and (src in servers) and (dst in servers)):
                if ( (src in servers1) and (dst in servers2) ) :
                    pathLen = 4
                elif ( (src in servers2) and (dst in servers1) ) :
                    pathLen = 4
                elif ( (src in servers3) and (dst in servers4) ) :
                    pathLen = 4
                elif ( (src in servers4) and (dst in servers3) ) :
                    pathLen = 4
                elif ( (src in servers5) and (dst in servers6) ) :
                    pathLen = 4
                elif ( (src in servers6) and (dst in servers5) ) :
                    pathLen = 4
                elif ( (src in servers7) and (dst in servers8) ) :
                    pathLen = 4
                elif ( (src in servers8) and (dst in servers7) ) :
                    pathLen = 4
                elif ( (src in servers1) and (dst in servers1) ) :
                    pathLen = 2
                elif ( (src in servers2) and (dst in servers2) ) :
                    pathLen = 2
                elif ( (src in servers3) and (dst in servers3) ) :
                    pathLen = 2
                elif ( (src in servers4) and (dst in servers4) ) :
                    pathLen = 2
                elif ( (src in servers5) and (dst in servers5) ) :
                    pathLen = 2
                elif ( (src in servers6) and (dst in servers6) ) :
                    pathLen = 2
                elif ( (src in servers7) and (dst in servers7) ) :
                    pathLen = 2
                elif ( (src in servers8) and (dst in servers8) ) :
                    pathLen = 2
                else:
                    pathLen = 6
                    
                paths = nx.all_simple_paths(G, source=src, target=dst, cutoff=pathLen) 
                      
                for p in paths:
                    f.write(str(Num_Nodes_arr[x]))
                    f.write("-")
                    f.write(str(Num_Nodes_arr[y]))
                    f.write(" ")
                    edgesinpath=zip(p[0:],p[1:]) 
                    
                    path_nodes = []        
                    
                    for e in edgesinpath:
                        path_nodes.extend(e)

                    sc = 0
                    arr_length = len(path_nodes) - 3
                    
                    if(arr_length > 1):
                        for n in range(1,arr_length):
                            if (sc + 2 < len(path_nodes)):
                                s = str(path_nodes[sc]) + '-' + str(path_nodes[sc+1])
                                sc = sc + 2
                                f.write(s)
                                f.write(',')
                    
                    if(arr_length <= 1):
                        s1 = str(path_nodes[0]) + '-' + str(path_nodes[1])
                        f.write(s1)
                        f.write(',')
                        
                    sn = str(path_nodes[arr_length+1]) + '-' + str(path_nodes[arr_length+2])
                    f.write(sn)
                    f.write('\n')
            
    f.close()
    
    for s in range (1, MidSwitchesStarts):
        li = str(s) + " "
        FI.write(li)
        if s in servers1:
            l = str(EdgeSwitchesStart) + "-" + str(MidSwitchesStarts) + "," + str(MidSwitchesStarts) + "-" + str(MidSwitchesStarts + 2) + "," + str(MidSwitchesStarts+2) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers2:
            l = str(EdgeSwitchesStart) + "-" + str(MidSwitchesStarts) + "," + str(MidSwitchesStarts) + "-" + str(MidSwitchesStarts + 3) + "," + str(MidSwitchesStarts+3) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers3:
            l = str(EdgeSwitchesStart) + "-" + str(MidSwitchesStarts+4) + "," + str(MidSwitchesStarts+4) + "-" + str((MidSwitchesStarts + 4) + 2) + "," + str((MidSwitchesStarts + 4) + 2) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers4:
            l = str(EdgeSwitchesStart) + "-" + str(MidSwitchesStarts+4) + "," + str(MidSwitchesStarts+4) + "-" + str((MidSwitchesStarts + 4) + 3) + "," + str((MidSwitchesStarts + 4) + 3) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers5:
            l = str(EdgeSwitchesStart+2) + "-" + str(MidSwitchesStarts+8) + "," + str(MidSwitchesStarts+8) + "-" + str((MidSwitchesStarts + 8) + 2) + "," + str((MidSwitchesStarts + 8) + 2) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers6:
            l = str(EdgeSwitchesStart+2) + "-" + str(MidSwitchesStarts+8) + "," + str(MidSwitchesStarts+8) + "-" + str((MidSwitchesStarts + 8) + 3) + "," + str((MidSwitchesStarts + 8) + 3) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers7:
            l = str(EdgeSwitchesStart+2) + "-" + str(MidSwitchesStarts+12) + "," + str(MidSwitchesStarts+12) + "-" + str((MidSwitchesStarts + 12) + 2) + "," + str((MidSwitchesStarts + 12) + 2) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
        elif s in servers8:
            l = str(EdgeSwitchesStart+2) + "-" + str(MidSwitchesStarts+12) + "," + str(MidSwitchesStarts+12) + "-" + str((MidSwitchesStarts + 12) + 3) + "," + str((MidSwitchesStarts + 12) + 3) + "-" + str(s)
            FI.write(l)
            FI.write('\n')
    
    FI.close()
    
    for s in range (1, MidSwitchesStarts):
        li = str(s) + " "
        FO.write(li)
        
        if s in servers1:
            l = str(EdgeSwitchesStart+1) + "-" + str(MidSwitchesStarts+1) + "," + str(MidSwitchesStarts+1) + "-" + str((MidSwitchesStarts+1) + 1) + "," + str((MidSwitchesStarts+1) + 1) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers2:
            l = str(EdgeSwitchesStart+1) + "-" + str(MidSwitchesStarts+1) + "," + str(MidSwitchesStarts+1) + "-" + str((MidSwitchesStarts+1) + 2) + "," + str((MidSwitchesStarts+1) + 2) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers3:
            l = str(EdgeSwitchesStart+1) + "-" + str(MidSwitchesStarts+5) + "," + str(MidSwitchesStarts+5) + "-" + str((MidSwitchesStarts + 5) + 1) + "," + str((MidSwitchesStarts + 5) + 1) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers4:
            l = str(EdgeSwitchesStart+1) + "-" + str(MidSwitchesStarts+5) + "," + str(MidSwitchesStarts+5) + "-" + str((MidSwitchesStarts + 5) + 2) + "," + str((MidSwitchesStarts + 5) + 2) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers5:
            l = str(EdgeSwitchesStart+3) + "-" + str(MidSwitchesStarts+9) + "," + str(MidSwitchesStarts+9) + "-" + str((MidSwitchesStarts + 9) + 1) + "," + str((MidSwitchesStarts + 9) + 1) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers6:
            l = str(EdgeSwitchesStart+3) + "-" + str(MidSwitchesStarts+9) + "," + str(MidSwitchesStarts+9) + "-" + str((MidSwitchesStarts + 9) + 2) + "," + str((MidSwitchesStarts + 9) + 2) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers7:
            l = str(EdgeSwitchesStart+3) + "-" + str(MidSwitchesStarts+13) + "," + str(MidSwitchesStarts+13) + "-" + str((MidSwitchesStarts + 13) + 1) + "," + str((MidSwitchesStarts + 13) + 1) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
        elif s in servers8:
            l = str(EdgeSwitchesStart+3) + "-" + str(MidSwitchesStarts+13) + "," + str(MidSwitchesStarts+13) + "-" + str((MidSwitchesStarts + 13) + 2) + "," + str((MidSwitchesStarts + 13) + 2) + "-" + str(s)
            FO.write(l)
            FO.write('\n')
    
    FO.close()
    
        
#--------------------------------------------- End of def main'''

import networkx as nx
from random import randint
import sys
import matplotlib.pyplot as ppt

main_as_def()
        