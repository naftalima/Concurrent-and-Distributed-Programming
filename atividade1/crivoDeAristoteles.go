package main

import	("fmt"
				"sync")

var (
	mu sync.Mutex
	numeros [101]int
)

func Crivo(position int) {
	mu.Lock() 
	mu.Unlock()
}

func main() {
	for i := 0; i < 101; i++ {
		if i == 0 || i == 1 {
			numeros[i] = -1 
		} else {
			numeros[i] = i
		}
	}
	
	// ch <- Crivo(2)
	// ch <- Crivo(3)
	// ch <- Crivo(4)
	for i := 2; i <= 10; i++ {
		for j := i + i; j < 101; j = j + i {
			numeros[j] = -1
		}
	}
	
	for i := 1; i < 101; i++ {
		if numeros[i] != -1 {
			fmt.Printf("%v ", i)
		}
	}
}