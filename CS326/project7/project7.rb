#!/usr/bin/env ruby
require 'csv'

$debugging = false
$classTitle = ""
$asstCount = 0 
$testCount= 0 
$weightAssts = 0
$weightTests = 0
$colLabels = []
$maxScores = []
$gradeData = []
$useName = false
$asstTotalMaxPoints = 0
$testTotalMaxPoints = 0

class Student
    attr_accessor :id, :name, :asstScores, :testScores, :grade
    def initialize(id, name, asstScores, testScores)
        @id = id
        @name = name 
        @asstScores = asstScores
        @testScores = testScores
        @asstPoints = 0.0 
        
        asstScores.each do |i|
            @asstPoints = @asstPoints + i.to_f
        end 
        
        @testPoints = 0
        testScores.each do |i|
            @testPoints = @testPoints + i.to_f
        end
        @grade = (@testPoints / $testTotalMaxPoints)*( $weightTests.to_f )  + (@asstPoints / $asstTotalMaxPoints) * ($weightAssts.to_f )
    end

end
def debug(string, val)
    if $debugging == true
        print string
        print ": "
        print val
        puts ""
    end
end

def getDatafromFile()
    dataFile = CSV.read("scores1.csv")
    $classTitle = dataFile[0][1].to_s
    dataFile.shift
    $asstCount = dataFile[0][2].to_i
    dataFile.shift
    $testCount = dataFile[0][2].to_i
    dataFile.shift
    $weightAssts = dataFile[0][2].to_i
    dataFile.shift
    $weightTests = dataFile[0][2].to_i
    dataFile.shift
    $colLabels = dataFile[0]
    $colLabels.shift
    $colLabels[0] =""
    dataFile.shift
    #puts "asst"
    $maxScores = dataFile[0]
    $maxScores.shift
    $maxScores.shift
    for i in 0..($asstCount - 1)
        #puts $maxScores[i]
        $asstTotalMaxPoints = $asstTotalMaxPoints + $maxScores[i].to_i
    end
    #puts "test"
    for i in $asstCount..($asstCount + $testCount - 1)
        #puts $maxScores[i].to_i
        $testTotalMaxPoints = $testTotalMaxPoints + $maxScores[i].to_i
    end
    dataFile.shift
    dataFile.each do |i|
        tempID = i[0].to_i
        tempName = i[1].to_s.downcase
        tempAssign = i.slice(2..(1 + $asstCount))
        tempTests =  i.slice((2 + $asstCount)..(1 + $asstCount + $testCount))
        $gradeData << Student.new(tempID, tempName, tempAssign, tempTests)
    end
end

def writeHTML ()
    puts("<!DOCTYPE html>\n<html>\n<style>\n   table, th, td {\n   border:1px solid black;\n}\n</style>\n<body>\n\n")
    puts("<table style=\"width:100%\">\n")
    puts("\t<tr>\n")
    $colLabels.each do |i|
        puts("\t\t<th>", i,"<th>\n")
    end
    puts("\t</tr>\n")
    
    $gradeData.each do |i|
        puts("\t<tr>\n")
        
        if $useName == true 
            puts("\t\t<th>", i.name,"<th>\n")
        else   
            puts("\t\t<th>", i.id,"<th>\n")
        end
        i.asstScores.each do |j|
            puts("\t\t<th>", j,"<th>\n")
        end
        i.testScores.each do |j|
            puts("\t\t<th>", j,"<th>\n")
        end
        puts("\t\t<th>", i.grade.round(2),"<th>\n")
        puts("\t</tr>\n")
    end
    
    puts("\t\t<th>Possible<th>\n")

    $maxScores.each do |i|
        puts("\t\t<th>", i,"<th>\n")
    end
    puts("</table>\n</body>\n</html>\n")
end

#MAIN
if ARGV[0] == "-names" 
    $useName = true
end
getDatafromFile()
writeHTML()





