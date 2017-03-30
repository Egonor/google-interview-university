#! python3
#	MERGE SORT *Pseudocode


def merge( A, B ):
	if len(A) == 0:
		return B
	if len(B) == 0:
		return A
	if A[0] < B[0]:
		return concat(A[0], merge( A[], B ))
	else:
		return concat(B[0], merge( A, B[len(B)] ))


def mergeSort (A, n):
	n = len(A)
	if n == 1:
		return A
	middle = math.floor(n / 2)
	leftHalf = [A..middle]
	rightHalf = A[ (middle + 1) ... n]
	return merge( mergeSort(lefHalf, middle), mergeSort(rightHalf, n - middle))


arrayOne = [0, 1, 2, 3, 4]
arrayTwo = [5, 6, 7, 8, 9]

print(mergeRec(arrayOne, arrayTwo))