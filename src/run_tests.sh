gcc app.c -o app

xterm -hold -e "echo Step 1: & ./app read" &
xterm -hold -e "echo Step 2: & ./app read" &
xterm -hold -e "echo Step 3: & ./app read" &
xterm -hold -e "echo Step 4: & ./app write alpha-Centauri" &
xterm -hold -e "echo Step 5: & ./app write Sirius" &
xterm -hold -e "echo Step 6: & ./app read" &
xterm -hold -e "echo Step 7: & ./app write eta-Eridani" &
xterm -hold -e "echo Step 8: & ./app read" &
xterm -hold -e "echo Step 9: & ./app write 61-Cygni" &
xterm -hold -e "echo Step 10: & ./app read" &