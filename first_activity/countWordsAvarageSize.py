from time import perf_counter

def countAvarage(file, bookName):
  data = file.read()
  words = data.split()
  charCount = 0

  for word in words:
    charCount += len(word)

  print(bookName + ": " + str(charCount/len(words)))

def main():
  hungerGames = open("the_hunger_games.txt", "r")
  prideAndPrejudice = open("pride_and_prejudice.txt", "r")
  sherlockHolmes = open("sherlock_holmes.txt", "r")
  theFellowshipOfTheRing = open("the_fellowship_of_the_ring.txt", "r", encoding="ISO-8859-1")
  bible = open("biblia.txt", "r")

  start_time = perf_counter()

  countAvarage(hungerGames, "Hunger Games")
  countAvarage(prideAndPrejudice, "Pride and Prejudice")
  countAvarage(sherlockHolmes, "Sherlock Holmes")
  countAvarage(theFellowshipOfTheRing, "The Fellowship Of The Ring")
  countAvarage(bible, "Bible")

  end_time = perf_counter()
  print(f'It took {end_time- start_time: 0.4f} second(s) to complete.')
  

if __name__ == "__main__":
    main()