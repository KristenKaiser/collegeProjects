#!/usr/bin/env ruby
$debugging = false
valueList ={ 'A' => 1, 'F' => 4, 'K' => 5, 'P' => 3, 'U' => 1,
            'B' => 2, 'G' => 2, 'L' => 1, 'Q' => 10, 'V' => 4,
            'C' => 3, 'H' => 4, 'M' => 3, 'R' => 1, 'W' => 4,
            'D' => 2, 'I' => 1, 'N' => 1, 'S' => 1, 'X' => 8,
            'E' => 1, 'J' => 8, 'O' => 1, 'T' => 1, 'Y' => 4,
            'Z' => 10 
            }


def debug(string, val)
    if $debugging == true
        print string
        print ": "
        print val
        puts ""
    end
end

def expandString(word)
    exString = ""
    position = word.size - 2
    while position >= 0 do
        # multipliers
        if word[position, 1] == "2" || word[position, 1] == "3"     #   account for multipliers
            for i in 1 .. Integer(word[position, 1]) - 1 do     
                if position == 0                                    #   duplicate word
                    exString << exString
                else                                                #   duplicate letter
                    exString << word[position - 1, 1]
                end
            end
            position = position - 1 
        end 
        exString << word[position, 1]
        position = position - 1
    end
    exString
end 

#asks user for word and error checks it
#returns string or 0 
def getWord
    print "\n Enter a word: "
    isPrevNum = false
    word = gets.upcase
    word.strip.each_char do |c| 
        debug("char", c)
        if c == '2' || c == '3'                     #   validate multipliers 
            if isPrevNum == true
                print "error, found bad number: \'"
                print c
                print "\'\n"
                return -1
            else
                debug(c, isPrevNum)
                isPrevNum = true
            end
        elsif ('A' > c || c > 'Z')                  #   validate characters 
            
            puts "      error: invalid input"
            if c == ' '
                puts "      please enter 1 word at a time"
            else
                print "      bad character: "
                print c
                #print " letter "
            end
            return -1
        else
            isPrevNum = false
        end 
        debug("     ", "success")
        
    end
    return word
end

#   start main
puts "\nScrabble Score Calculator\n"
continue = true
while continue == true do
    word = getWord
    originalWord = word
    debug("word size", word.size)
    if word.size - 1 == 0 
        puts "\n  Good-bye!"
        continue = false
    end
    if word != -1 && continue == true
        word = expandString(word).strip
        debug("expanded string", word)
        score = 0
        chars = word.each_char.to_a
        chars.each do |c|
            score = score + valueList[c.upcase]
            debug(c, score)
        end
        print "     Score for \'"
        print originalWord.strip
        print "\' is: "
        print score
        puts ""
    end
end
#todo
#repeat untill blank word returned
#remove testing code
