#for x in {0..3}; do
#    for i in {501..511}; do cat OLA1-input.txt | python ./random_board.py $i 5000 | python ./a-star.py $x; done > ${x}-a.txt;
#done;
#
#count=0
#for t in {0..99}; do 
#    for i in {1,2,3,5}; do 
#        for x in {10,50,100,1000}; do 
#            count=$((count + 1))
#            python greedy.py $t $i $x &
#            if ((count=5)); then
#                wait
#                count=0
#            fi
#        done;
#    done;
#done > greedy-compile.txt;

for t in {50..99}; do 
    for i in {1,2,3,5}; do 
        for x in {10,50,100,1000}; do 
            count=$((count + 1))
            python sa.py $t $i $x &
            if ((count=5)); then
                wait
                count=0
            fi
        done;
    done;
done > sa-compile.txt;


#for x in {0..3}; do
#    cat ${x}-a.txt | grep 'N' | cut -f2 -d'=' > N-${x}.txt;
#    cat ${x}-a.txt | grep 'd' | cut -f2 -d'=' > d-${x}.txt;
#    cat ${x}-a.txt | grep 'b' | cut -f2 -d'=' > b-${x}.txt;
#    cat ${x}-a.txt | grep 'V' | cut -f2 -d'=' > V-${x}.txt;
#    cat ${x}-a.txt | grep 't' | cut -f2 -d'=' > t-${x}.txt;
#    paste ?-${x}.txt > table-${x}.txt;
#done;


