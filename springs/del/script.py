import math

#springs
#p1 p2 spring_const damping_cont rest_len r g b

def calcParticles(nodes, cX, cY, r):
    particles = []

    centerMass = [350, 250, 0, 0, 1, 1]
    particles.append(centerMass)

    space = 1

    for i in range(nodes):
        l =  425#2 + 2 * i
        x = cX + (l * math.cos(math.radians(i*space))) 
        y = cY + (l * math.sin(math.radians(i*space))) 
        dx = 0
        dy = 0
        anchored = 0
        newParticle = [x, y, dx, dy, r, anchored , 1]
        particles.append(newParticle)
    
    return particles

def calcSprings(nodes, particles, colors):
    springs = []
    spring_const = 2
    damping_const = .1

    ci = 1 * (len(colors)//nodes)
    
    for i in range(1, nodes + 1):
        p1 = 0
        p2 = i
        j = i * ci
        newSpring = [p1, p2, spring_const, damping_const/10, particles[i][6], colors[j][0], colors[j][1], colors[j][2]]
        springs.append(newSpring)

    return springs

def createData(particles, springs):
    fin = open("data.txt", "w")
    for p in particles:
        particle = "particle " + str(p[0]) + " " + str(p[1]) + " " + str(p[2]) + " " + str(p[3]) + " " + str(p[4]) + " " + str(p[5]) + "\n"
        fin.write(particle)
    for s in springs:
        spring = "spring " + str(s[0]) + " " + str(s[1]) + " " + str(s[2]) + " " + str(s[3]) + " " + str(s[4]) + " " + str(s[5]) + " " + str(s[6]) + " " + str(s[7]) + "\n"
        fin.write(spring)
    fin.write("DeltaT" + " .02\n")
    fin.close()

def createColors():
    colors = []
    fin = open("color.txt", "r")
    for line in fin:
        line = line.split()
        color = [line[0], line[1], line[2]]
        colors.append(color)

    return colors



def main():
    colors = createColors()
    nodes = 360
    r = 5
    cX = 350
    cY = 250
    particles = calcParticles(nodes, cX, cY, r)
    springs = calcSprings(nodes, particles, colors)
    createData(particles, springs)


main()