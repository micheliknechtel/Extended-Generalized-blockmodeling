for file in ./data/500/* ; do
   echo "$1" > $file".tmp";
   cat  $file >> $file".tmp";
   mv  $file".tmp" $file;
done