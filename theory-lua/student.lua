--[[
Check scores.lua on how to run program

Hunter Esler
Dr. Zhijiang Dong
CSCI 3210
20 April 2020

Student class
Initialize with c# and then scores, has relevant print information and setters/getters.
Create new student with Student:New()

]]


local StudentMeta = {}
Student = {}
--[[
    Creates a new student "object" with given parameters and returns it.
    local student = Student:New("c1", 0, 0.1, 0, 0, 99.5)
    student:PrintInformation()
]]
function Student:New(cn, cla, ola, quizscore, examscore, finalscore)
    local tbl = {}
    tbl.__index = tbl
    setmetatable(tbl, {__index=StudentMeta})
    tbl._students = {}
    --set member variabels
    --"private" members... don't touch!.. there isn't private members in lua
    tbl._cn = cn
    tbl._cla = tonumber(cla)
    tbl._ola = tonumber(ola)
    tbl._quizscore = tonumber(quizscore)
    tbl._examscore = tonumber(examscore)
    tbl._finalscore = tonumber(finalscore)
    tbl._totalscore = 0
    tbl:CalcTotalScore();
    return tbl
end

--[[
    Prints a formated string of each attribute for the student.
    To be used with roster:PrintTableKey()

    student:PrintInformation() 
    c1234501   10.00  20.00  10.00  30.00  30.00  100.00  A
]]
function StudentMeta:PrintInformation()
    local lettergrade = self:CalcLetterGrade()
    print(string.format("%-10s %-6.2f %-6.2f %-6.2f %-6.2f %-6.2f %-7.2f %s",
        self._cn,
        self._cla,
        self._ola,
        self._quizscore,
        self._examscore,
        self._finalscore,
        self._totalscore,
        lettergrade
    )
    )
end

--[[
    Setters and getters for each attribute of student. Pretty straight forward....
    student:SetCLA(1)
    student:GetCLA()
    1

    ..etc
]]
function StudentMeta:SetCLA(n)
    n = tonumber(n)
    if not n then
        error("val is not a number")
    end
    self._cla = n
    return self._cla
end

function StudentMeta:GetCLA()
    return self._cla
end

function StudentMeta:SetOLA(n)
    n = tonumber(n)
    if not n then
        error("val is not a number")
    end
    self._ola = n
    return self._ola
end
function StudentMeta:GetOLA()
    return self._ola
end

function StudentMeta:SetQuizScore(n)
    n = tonumber(n)
    if not n then
        error("val is not a number")
    end
    self._quizscore = n
    return self._quizscore
end
function StudentMeta:GetQuizScore()
    return self._quizscore
end

function StudentMeta:SetExamScore(n)
    n = tonumber(n)
    if not n then
        error("val is not a number")
    end
    self._examscore = n
    return self._examscore
end
function StudentMeta:GetExamScore()
    return self._examscore
end

function StudentMeta:SetFinalScore(n)
    n = tonumber(n)
    if not n then
        error("val is not a number")
    end
    self._finalscore = n
    return self._finalscore
end
function StudentMeta:GetFinalScore()
    return self._finalscore
end

function StudentMeta:GetCNum()
    return self._cn
end

function StudentMeta:CalcTotalScore()
    self._totalscore = self._cla + self._ola + self._quizscore + self._examscore + self._finalscore
end

--[[
    Calcs total score as well as returns it.
]]
function StudentMeta:GetTotalScore()
    self:CalcTotalScore()
    return self._totalscore
end

--[[
    Calculates the letter grade for this student by getting the total score
     and using the given grade table returns a string.
    student:CalcLetterGrade()
    B-
]]
function StudentMeta:CalcLetterGrade()
    local s = self:GetTotalScore()
    if s >= 90 then
        return "A"
    elseif s >= 87 then
        return "B+"
    elseif s >= 83 then
        return "B"
    elseif s >= 80 then
        return "B-"
    elseif s >= 77 then
        return "C+"
    elseif s >= 73 then
        return "C"
    elseif s >= 70 then
        return "C-"
    elseif s >= 67 then
        return "D+"
    elseif s >= 63 then
        return "D"
    elseif s >= 60 then
        return "D-"
    else
        return "F"
    end
end