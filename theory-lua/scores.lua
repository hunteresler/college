--main file. run this

--[[
Hunter Esler
Dr. Zhijiang Dong
CSCI 3210
20 April 2020
Designed and implemented student and roster classes to parse scores.txt
to demonstrate my knowledge of my chosen language

To run this program, do (lua binary file here) student.lua
lua53.exe is from lua.org and can be used on windows.

]]

--Load student and roster classes.
require("student")--student.lua
require("roster")--roster.lua

--change number of queries before full query
local NUM_QUERIES = 2

local roster = Roster:New()

--Grabs name of the grade file from input, and checks if the file exists.
print("What is the name of the grade file? : ")
local fname = io.read()
local file = io.open(fname)

if not file then
    print("The file '" .. fname .. "' could not be found.")
    return 
end

roster:LoadFile(file)--roster loads file in roster class

--Reads input for NUM_QUERIES times to check c# in the loaded grade file.
for i = 1, NUM_QUERIES do
    --repeat until correct input.
    local a = true
    while a do
        print("\nEnter a C# to query: ")
        local cnum = io.read()
        local match = string.match(cnum , "[cC][0-9]*")
        --input matches perfectly
        if match==cnum then
            print()
            roster:Query(cnum)
            a = false
        else
            print("Wrong format. Format is c followed by any amount of numbers.")
        end
    end
end

--Prints all student scores
print("\nAll students")
roster:PrintStudents()

--Prints all averages and maxs
local acla, aola, aquiz, aexam, afinal, atotal = roster:GetAverages()
local cla,ola,quiz,exam,final,total = roster:GetMaxs()
print("Average CLA:   " .. string.format("%.2f ", acla))
print("Max CLA:       " .. cla .. "\n")
print("Average OLA:   " .. string.format("%.2f ", aola))
print("Max OLA:       " .. ola .. "\n")
print("Average Quiz:  " .. string.format("%.2f ", aquiz))
print("Max Quiz:      " .. quiz .. "\n")
print("Average Exam:  " .. string.format("%.2f ", aexam))
print("Max Exam:      " .. exam .. "\n")
print("Average Final: " .. string.format("%.2f ", afinal))
print("Max Final:     " .. final .. "\n")

file:close()