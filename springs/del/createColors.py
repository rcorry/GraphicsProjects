def main():
    r = 255
    g = 0
    b = 0
    fin = open("color.txt", "w")
    fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        g += 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        r -= 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        b += 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        g -= 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        r += 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")
    for i in range(1, 256):
        b -= 1
        fin.write(str(r) + " " + str(g) + " " + str(b) + "\n")

    fin.close()

main()
