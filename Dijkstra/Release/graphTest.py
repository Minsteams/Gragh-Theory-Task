import random
import time
import msvcrt
import os

log=open('log_graph.txt','w')#日志

def logprint(content):
    global log
    print(content)
    log.write(content)

def loginput(content):
    global log
    log.write(content)
    result=input(content)
    log.write(result)
    log.write("\n")
    return result
    
def genRandomVector(fileName,VCount,EdgeCount,MaxWeight):
    outp=open(fileName,'w')
    outp.write("%i\n"%(VCount))
    i = 0
    while i<VCount:
        en=random.randint(0,EdgeCount)
        mLine="%i %i"%(i,en)
        j=0
        jovertect=0
        top=-1
        bottom=VCount+1
        t=-1
        while j<en:
            t=random.randint(0,VCount)
            if (t>top or t<bottom or jovertect>VCount)and t!=i:
                if t>top:
                    top=t
                if t<bottom:
                    bottom=t
                mLine+=" %i %i"%(t,random.randint(1,MaxWeight))
                j+=1
            jovertect+=1
        mLine+="\n"
        outp.write(mLine)
        i+=1
    outp.close()

def dtime(file,word):
    logprint('\nPress any key to continue...')
    stinfo=os.stat(file)
    logprint('\n'+word);
    logprint('Use time:%f'%(stinfo.st_mtime - stinfo.st_atime))

if __name__ == "__main__":
    random.seed()
    VCount=eval(loginput('Vertexes Count:'))
    EdgeCount=eval(loginput('Max edges of each vertex Count:'))
    MaxWeight=eval(loginput('Max weight of each edge:'))
    
    start = time.time()
    genRandomVector('in_graph.txt',VCount,EdgeCount,MaxWeight)
    end = time.time()
    logprint('Test data created!\nUse time:%lf'%(end-start))
    
    os.system('Dijkstra.exe')

    dtime('out_graph.txt','Graph created!')
    dtime('out_graphTree.txt','Tree created!')
    dtime('out_graphMatrix.txt','Matrix created!')
    log.close()
    msvcrt.getch();
