for file in ./network/* ; do
   echo "$1" > $file".tmp";
   cat  $file >> $file".tmp";
   mv  $file".tmp" $file;
done