CS350 Program1 <br/>
Daelin Fischman <br/>
Nuri Ra <br/>
Lynda Ademola <br/>

-------------
The Least Recently used Algorithm is accepted as an approximation of an optimal Algorithm. However, certain factors, such as spatial locality and program phases might make variations on the LRU perform better. We tested a pure LRU, against a LRU that selected only from the calling processes pages, an LRU that prefetched spatially close pages, and an LRU that selects a random page from within the processes own pages. We also tested a random page replacement as a control.input file


INTRO
-----
Page replacement has a very important role in the functioning of memory on a computer, which is essential to the overall operation of a computer. We investigated the Least Recently Used Algorithm, and variations on that Algorithm.

QUESTION
--------
The Least Recently used Algorithm is accepted as an approximation of an optimal Algorithm. However, certain factors, such as spatial locality and program phases might make variations on the LRU perform better. We tested a pure LRU, against a LRU that selected only from the calling processes pages, an LRU that prefetched spatially close pages, and an LRU that selects a random page from within the processes own pages. We also tested a random page replacement as a control.

TESTS
----
We tested our methods using different combinations of variables from lab4. The main differences came about when Locality was turned on or off, how many memory frames were allocated, and how many references were made.

./lab5 800 <input>
./lab5 900 <input>
./lab5 1000 <input>
./lab5 2500 <input>

RESULTS

	Algorithm 2 performed better tham the pure LRU when locality was turned on, as was expected. When locality was turned off it performed much worse. Algorithms 1 and 3 performed
generally the same as each other and a bit behind the pure LRU, while random page replacement always performed badly.

-------

CONCLUSION
	Our results seem to indicate that pre-fetching is usually a good idea becuase locality will generally happen. However, questions remain about how many pages to prefetch, or
if prefetching always works. A LRU page replacement strategy will always perform well however.
----------

Test Cases:
* w/ and w/o phasing
* Different Memory Sizes
  - Base line memory size should be around 1000
* Locality Turned on and off
