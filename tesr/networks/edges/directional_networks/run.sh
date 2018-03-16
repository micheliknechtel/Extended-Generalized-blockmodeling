rm ./data/statistics/*.dat ./data/network/*.dat ./data/community/*.dat ./data/seed/*.dat
i=1
cat input_02.txt | while read line;
        do
            for j in $(seq 1 1)
             do
            	echo $line;
                	./directional_networks -$line;
                	f=`printf %03d $i`;
                	l=`printf %03d $j`;
                	mv network.dat  ./data/network/"${line// /_}"_network_$f"_"$l.dat;
                	mv statistics.dat   ./data/statistics/"${line// /_}"_statistics_$f"_"$l.dat;
                	mv community.dat	./data/community/"${line// /_}"_community_$f"_"$l.dat;
                	cat time_seed.dat >>	./data/seed/"${line// /_}"_time_seed_$f"_"$l.dat;
                	sleep 1;
                done
            #echo -e "$(sed '1d' input.txt)">input.txt
            i=$((i+1));
        done
for file in ./data/network/* ./data/statistics/* ./data/community/* ./data/seed/*; do
    mv ./"$file" "${file//-/_}"
done
for file in `ls  ./data/network/* | grep *.dat >` ; do
   echo $1 > $file".tmp";
   cat  $file >> $file".tmp";
   mv  $file".tmp" $file;
done
echo "Number of genereted files in network:";
 ls -l ./data/network/| grep -v ^l | wc -l
 echo "Number of genereted files in statistics:";
 ls -l ./data/statistics/| grep -v ^l | wc -l
 echo "Number of genereted files in community:";
 ls -l ./data/community/| grep -v ^l | wc -l
# rm ./data/statistics/*.dat ./data/network/*.dat ./data/community/*.dat ./data/seed/*.dat
# ls ./data/statistics/*.dat ./data/network/*.dat ./data/community/*.dat ./data/seed/*.dat
#egrep -e "Relation Matrix                  = N_30__k_20__mu_0.6|Solution|Minimal|Gap|Elapsed|EmptyCluster|Nodes" output.txt