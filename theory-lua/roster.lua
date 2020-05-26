--[[
Check scores.lua on how to run program

Hunter Esler
Dr. Zhijiang Dong
CSCI 3210
20 April 2020

Roster class, create the roster, and then load an already opened file with LoadFile
local file = io.open("file.txt")
local roster = Roster:New()
roster:LoadFile(file)
file:close()
]]

local RosterMeta = {}
Roster = {}
--[[
    Creates a new Roster "object" to be ready for loading a file
]]
function Roster:New()
    local tbl = {}
    tbl.__index = tbl
    setmetatable(tbl, {__index=RosterMeta})
    tbl._students = {}
    tbl._numstudents = 0
    return tbl
end

--[[
    Adds a already created student to our students table.
    roster:AddStudent(Student:New(...))
]]
function RosterMeta:AddStudent(student)
    self._students[student:GetCNum()] = student
    self._numstudents = self._numstudents + 1
end

--[[
    Tries to find a student with given cnum, and prints information of student if found.
    roster:Query("c1")
    Student not found!
]]
function RosterMeta:Query(cnum)
    if not cnum then return end
    local student = self:GetStudent(cnum)
    if student then
        --student:PrintTableKey()
        self:PrintTableKey()
        student:PrintInformation()
    else
        print("Student not found!")
    end
end

--[[
    Gets the averages of all the types of scores for our students.
    roster:GetAverages()
    0.0, 1.0, 2.0, 3.0, 4.0, 42.0
]]
function RosterMeta:GetAverages()
    local total = 0
    local cla = 0
    local ola = 0
    local quiz = 0
    local exam = 0
    local final = 0
    for _,student in pairs(self._students) do
        cla = cla     + student:GetCLA()
        ola = ola     + student:GetOLA()
        quiz = quiz   + student:GetQuizScore()
        exam = exam   + student:GetExamScore()
        final = final + student:GetFinalScore()
        total = total + student:GetTotalScore()
    end
    local div = self._numstudents
    total = total / div
    cla = cla / div
    ola = ola / div
    quiz = quiz / div
    exam = exam / div
    final = final / div
    return cla,ola,quiz,exam,final,total
end

--[[
    Returns maxs for all types of scores for our students.
    roster:GetMaxs()
    100.0 20.0 3.0 40.0 21.6 1100.0
]]
function RosterMeta:GetMaxs()
    local maxcla = 0
    local maxola = 0
    local maxquiz = 0
    local maxexam = 0
    local maxfinal = 0
    local maxtotal = 0
    for _, student in pairs(self._students) do
        if student:GetCLA() > maxcla then
            maxcla = student:GetCLA()
        end
        if student:GetOLA() > maxola then
            maxola = student:GetOLA()
        end
        if student:GetQuizScore() > maxquiz then
            maxquiz = student:GetQuizScore()
        end
        if student:GetExamScore() > maxexam then
            maxexam = student:GetExamScore()
        end
        if student:GetFinalScore() > maxfinal then
            maxfinal = student:GetFinalScore()
        end
        if student:GetTotalScore() > maxtotal then
            maxtotal = student:GetTotalScore()
        end
    end
    return maxcla, maxola, maxquiz, maxexam, maxfinal, maxtotal
end

--[[
    Prints the table key for printing out a table in console.
    roster:PrintTableKey()
    C#         CLA    OLA    Quiz   Exam   Final  Total   Letter grade
]]
function RosterMeta:PrintTableKey()
    print(string.format("%-10s %-6s %-6s %-6s %-6s %-6s %-7s Letter grade","C#","CLA","OLA","Quiz","Exam","Final","Total"))
end

--[[
    Tries to find a student with the given cnum string.
    roster:GetStudent("c1")
    table: 0x2919a94
]]
function RosterMeta:GetStudent(cnum)
    return self._students[tostring(cnum or "")]
end

--[[
    Calls student:PrintInformation() for every student.
    To be used in conjunction with PrintTableKey
    self:PrintStudents()
    c1234501   10.00  20.00  10.00  30.00  30.00  100.00  A
    c1232341   10.00  20.00  10.00  30.00  30.00  100.00  A--pretend theses are different
    c1231101   10.00  20.00  10.00  30.00  30.00  100.00  A
]]
function RosterMeta:PrintStudents()
    self:PrintTableKey()
    for v,i in pairs(self._students) do
        i:PrintInformation()
    end
end
--[[
    Calls the CalcLetterGrade for a student found with cnum string.
    roster:GetStudentLetterGrade("c1234501")
    "A"
]]
function RosterMeta:GetStudentLetterGrade(cnum)
    local student = self:GetStudent(cnum)
    if student then
        return student:CalcLetterGrade()
    end
    return nil
end

--helper func (meta, studentfunc, rosterfunc)
--makes updaters (setters) to work with student setters
local function addupdatefunc(m, sf, rf)
    m[rf] = function(self, cnum, val)
        val = tonumber(val)
        if not val then
            error("val is not a number")
        end
        local student = self:GetStudent(cnum)
        if student then
            student[sf](student,val)
        end
    end
end

--creates "Update" functions in format: roster:UpdateStudentBlah(cnumber, number)
addupdatefunc(RosterMeta, "SetCLA", "UpdateStudentCLA")
addupdatefunc(RosterMeta, "SetOLA", "UpdateStudentOLA")
addupdatefunc(RosterMeta, "SetQuizScore", "UpdateStudentQuizScore")
addupdatefunc(RosterMeta, "SetExamScore", "UpdateStudentExamScore")
addupdatefunc(RosterMeta, "SetFinalScore", "UpdateStudentFinalScore")

--[[
    Tries to find a student with given cnum and then calls their PrintInformation
    roster:QueryStudent("c1234501")
    C#         CLA    OLA    Quiz   Exam   Final  Total   Letter grade
    c1234501   10.00  20.00  10.00  30.00  30.00  100.00  A
]]
function RosterMeta:QueryStudent(cnum)
    local student = self:GetStudent(cnum)
    if not student then
        print("Student doesn't exist with C# " .. cnum)
        return
    end
    student:PrintInformation();

end

--[[
    Takes an already opened file and parses through it to create the students to be populated into the _students table.
    roster:LoadFile(file)
]]
function RosterMeta:LoadFile(file)
    --iterate each line
    local lines = {}
    local i = 1
    for l in file:lines() do
        --skip key of table
        if i > 1 then
            --each "line" is a table, containing each column in a line
            local line = {}
            --split string into seperate "words"
            for val in string.gmatch(l, "%S+") do
                table.insert(line, val)
            end
            --only 6 columns for each student
            if #line == 6 then
                table.insert(lines, line)
            else
                print("wrong number of columns at row "..i)
            end
        end
        i = i + 1
    end
    --as specified in the scores file, get each attribute for each student, and make a student object and add them to the roster.
    for k,v in pairs(lines) do
        local cnum = v[1]
        local cla = tonumber(v[2])
        local ola = tonumber(v[3])
        local quiz = tonumber(v[4])
        local exam = tonumber(v[5])
        local final = tonumber(v[6])
        if not cla or not ola or not quiz or not exam or not final then--input checking
            print("wrong format for line "..k)
        else
            --Create the actual student and add it to ourselves.
            local student = Student:New(cnum, cla, ola, quiz, exam, final)
            self:AddStudent(student)
        end
    end
    
end