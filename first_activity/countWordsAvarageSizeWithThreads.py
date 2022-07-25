from threading import Thread
from time import perf_counter

def countAvarage(bookPair):
  file, bookName = bookPair
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

  hungerGamesPair = (hungerGames, "Hunger Games")
  prideAndPrejudicePair = (prideAndPrejudice, "Pride and Prejudice")
  sherlockHolmesPair = (sherlockHolmes, "Sherlock Holmes")
  theFellowshipOfTheRingPair = (theFellowshipOfTheRing, "The Fellowship Of The Ring")
  biblePair = (bible, "Bible")

  books = [hungerGamesPair, prideAndPrejudicePair, sherlockHolmesPair, theFellowshipOfTheRingPair, biblePair]

  start_time = perf_counter()

  threads = []
  for n in books:
    t = Thread(target=countAvarage, args=(n,))
    threads.append(t)
    t.start()

  for t in threads:
    t.join()

  end_time = perf_counter()
  print(f'It took {end_time- start_time: 0.4f} second(s) to complete.')


if __name__ == "__main__":
    main()