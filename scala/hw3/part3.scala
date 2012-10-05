/**
 * 3. (5 pts) Write a function toBinary that takes a list of n integers in the
 * range [0 .. 255] inclusive (8 bit integers) and returns a single 8*n bit
 * string of 0 and 1 digits that corresponds to the binary representation of the
 * bytes in the list. For example toBinary( List(128, 1) ) should evaluate to
 * "1000000000000001." Notice that only one string is returned.
 *
 * Hint: Use the toBinaryStringFunctional method in the BinaryString.scala
 * sample file to convert the individual numbers. Think about using map, maybe
 * twice (you'll have to pad short strings on the left with "0" characters), and
 * then foldLeft to combine the individual strings.
 */
object Main {
    def main(args: Array[String]): Unit = {
        println("Hello, world!")
    }
}
