import math

#springs
#p1 p2 spring_const damping_cont rest_len r g b

def calcSpheres(num_spheres, cX, cY, r):
    particles = []

    centerMass = [350, 250, 0, 0, 1, 1]
    particles.append(centerMass)

    inc = float(1)/num_spheres;
    space = 360.0/num_spheres
    fout = open("model3.txt", "w")
    fout.write("""1 // version number
0 0 200 // eye
0 0 0 // at
0 1 0 // up
1 // distance to near plane
2000 // distance to far plane
45	// field of view
700 // screen_x
500 // screen_y

2 // number of point lights
-200 20 200 // light position
100 60 -120 // light position\n\n""")
    fout.write(str(1+num_spheres*27)+"\n")
    fout.write("0 0 -400\n")
    fout.write(str(r*10)+"\n")

    fout.write("1 1 0" + "\n" )
    fout.write(".5 .5 .5\n")
    fout.write(".5 .5 .5 50\n")
    for j in range(9):
        for i in range(num_spheres):
            l = 14.0-j 
    #        x = cX + (l * float(math.cos(float(math.radians(float(i)*space))))) 
    #        y = cY + (l * math.sin(math.radians(i*space))) 
            x = l*r*math.sin(math.radians(i*space))
            y = l*r*math.cos(math.radians(i*space))
            z = j*-30;
            dx = 0
            dy = 0
            fout.write(str(x) + " " + str(y) + " " + str(z)+"\n")
            fout.write(str(r)+"\n")

            fout.write(".12 .02 .14" + "\n" )
            fout.write(".6 .1 .7\n")
            fout.write(".5 .5 .5 50\n")
        for i in range(num_spheres):
            l = 14.0-j 
    #        x = cX + (l * float(math.cos(float(math.radians(float(i)*space))))) 
    #        y = cY + (l * math.sin(math.radians(i*space))) 
            x = l*r*math.sin(math.radians(-i*space))
            y = l*r*math.cos(math.radians(-i*space))
            z = -20-30*j;
            dx = 0
            dy = 0
            fout.write(str(x) + " " + str(y) + " " + str(z)+"\n")
            fout.write(str(r)+"\n")

            fout.write("1 .5 0" + "\n" )
            fout.write(".5 .5 .5\n")
            fout.write(".5 .5 .5 50\n")
            #fout.write(".3 .2 " + str(i*inc) + " 50\n" )
        for i in range(num_spheres):
            l = 14.0-j 
    #        x = cX + (l * float(math.cos(float(math.radians(float(i)*space))))) 
    #        y = cY + (l * math.sin(math.radians(i*space))) 
            x = l*r*math.sin(math.radians(i*space))
            y = l*r*math.cos(math.radians(i*space))
            z = -40-30*j;
            dx = 0
            dy = 0
            fout.write(str(x) + " " + str(y) + " " + str(z)+"\n")
            fout.write(str(r)+"\n")

            fout.write(".12 .02 .14" + "\n" )
            fout.write(".6 .1 .7\n")
            fout.write(".5 .5 .5 50\n")
            #fout.write(".3 .2 " + str(i*inc) + " 50\n" )
    fout.close()    



def main():
    num_spheres = 60
    r = 9.0
    cX = 0.0
    cY = 0.0
    calcSpheres(num_spheres, cX, cY, r)


main()