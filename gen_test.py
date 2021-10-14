import random

filepath = input("File path: ") + ".txt"
wordsCountSubstring =int(input("How much words in substring: "))
wordsCountText = int(input("How much words in text: "))

l = ['cat', 'Cat',  'CAT', 'Dog', 'DOG','DoG', 'dom', 'Dom', 'DoM', 'DOM',
        'Block','BLOcK', 'Glock', 'glock', 'Clock', 'CLOCK', 'MOOD', 'mood']

fileOut = open(filepath, 'w')

i = 0
sstr = ''
while(i < wordsCountSubstring):
    sstr = sstr + l[int(random.random()*len(l))] + ' '
    i = i+1;
sstr += '\n'

i = 0
while(i < wordsCountText):
    if(i%15 == 0 and i != 0):
        sstr = sstr + '\n'
    sstr = sstr + l[int(random.random()*len(l))] + ' '
    i = i+1;
fileOut.write(sstr)
fileOut.close()