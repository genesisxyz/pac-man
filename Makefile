VERSION1 = esercizio1/
VERSION2 = esercizio2/
VERSION3 = esercizio3/

all:
	cd $(VERSION1); make > /dev/null
	cd $(VERSION2); make > /dev/null
	cd $(VERSION3); make > /dev/null

	@ echo 
	@ echo $(VERSION1): Start Pac-Man Remake with ./$(VERSION1)pacman
	@ echo $(VERSION2): Start Pac-Man Remake with ./$(VERSION2)pacman
	@ echo $(VERSION3): Start Pac-Man Remake with ./$(VERSION3)pacman
	@ echo Warning: ./$(VERSION3)pacman goes in Segmentation Fault.
	@ echo

clean:
	rm -f $(VERSION1)pacman $(VERSION1)*.o
	rm -f $(VERSION2)pacman $(VERSION2)*.o
	rm -f $(VERSION3)pacman $(VERSION3)*.o
