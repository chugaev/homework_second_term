def filter_func(lst: List[Int], func: (Int) => Boolean): List[Int] = {
  if (lst.isEmpty) Nil else if (func(lst.head)) lst.head :: filter_func(lst.tail, func) else filter_func(lst.tail, func)
}
def isEven(x: Int): Boolean = {
  if (x % 2 == 0) true else false
}
