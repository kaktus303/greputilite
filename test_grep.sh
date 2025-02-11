#!/bin/bash
s21_grep="./s21_grep"
testingText1="TestText1.txt"
testingText2="TestText2.txt"
testingText3="TestText3.txt"
errorText="no_file.txt"
grepFile="grepFile.txt"
log_memory="log_memory.txt"
log_program="log_program.txt"
#valgrind="valgrind --tool=memcheck --leak-check=yes"
s21_grepFile="s21_grepFile.txt"
temp1="1"
temp2="E"
touch "$log_memory"
touch "$grepFile"
touch "$s21_grepFile"
touch "$testingText1"
touch "$testingText2"
touch "$testingText3"
echo "" > "$log_memory"
echo "" > "$log_program"
echo -e "123   456\nt\nis\ne\n789" > "$testingText1"
echo -e "two files   456\n\nt\n\n\n789" > "$testingText2"
echo -e "\n\n\n Three filEs \n \n   175\n\n\n\n\n751\nhello world\nthis is a test\nanother lines" > "$testingText3"
# "-ie" "-ve" "-ce" "-le" "-ne" "-ie" "-ive" "-ice" "-ile" "-ine" "-vce" "-vle" "-vne" "-cle" "-cne" "-lne"
# "-he" "-hie" "-hive" "-hice" "-hile" "-hine"
ARGS=("-e" "-ie" "-ve" "-ce" "-le" "-ne" "-ie" "-ive" "-ice" "-ile" "-ine" "-vce" "-vle" "-vne" "-cle" "-cne" "-lne" "-he" "-hie" "-hive" "-hice" "-hile" "-hine" "-se" "-sie" "-sive" "-sice" "-sile" "-sine" "-hf" "-if" "-ivf" "-hicf" "-ilf" "-hinf" "-of" "-iof" "-hicof" "-ilof" "-hinof")
cur=-1
count_complite=0
for ARGS in "${ARGS[@]}"; do
  if [ -x "$s21_grep" ]; then
    if [ $cur -lt 23 ]; then
      $s21_grep $ARGS "$temp1" $ARGS "$temp2" "$testingText1" "$testingText2" "$testingText3" > $s21_grepFile
      grep $ARGS "$temp1" $ARGS "$temp2" "$testingText1" "$testingText2" "$testingText3" > $grepFile
    elif [ $cur -lt 28 ]; then
      $s21_grep $ARGS "$temp1" $ARGS "$temp2" "$testingText1" "$testingText2" "$testingText3" "$errorText" > $s21_grepFile
      grep $ARGS "$temp1" $ARGS "$temp2" "$testingText1" "$testingText2" "$testingText3" "$errorText" > $grepFile
    elif [ $cur -lt 34 ]; then
      $s21_grep $ARGS "$testingText1" "$testingText2" "$testingText3" > $s21_grepFile
      grep $ARGS "$testingText1" "$testingText2" "$testingText3" > $grepFile
    else
      $s21_grep $ARGS "$testingText1" "$testingText2" "$testingText3" > $s21_grepFile
      grep $ARGS "$testingText1" "$testingText2" "$testingText3" > $grepFile
    fi
    ((cur+=1))
    echo -e "\n\n\n\n\n Test $cur : \n " >> "$log_memory"
    valgrind --tool=memcheck --leak-check=yes $s21_grep "$ARGS" "$temp1" "$ARGS" "$temp2" "$testingText1" "$testingText2" "$testingText3" >> "$log_memory" 2>&1
  else
    echo "Файл $s21_grep не найден или у него нет прав на выполнение."
  fi
echo -e "\n Test $cur : \n " >> "$log_program"
diff "$s21_grepFile" "$grepFile" >> "$log_program" 2>&1

if [ $? -eq 0 ]; then
    echo "Test $cur flags[$ARGS] COMPLITE."
    count_complite=$((count_complite+1))
else
    echo "Test $cur flags[$ARGS] ERROR."
fi
done
echo -e "\n All: \n Test program : $count_complite/"$((cur+1))
printf ' Test memory: %d/%d\n' $(grep -c "no leaks" $log_memory) $((cur+1))
printf ' Test ERROR SUMMARY: %d/%d\n' $(grep -c "0 errors from 0 contexts" $log_memory) $((cur+1))
# rm -r TestText1.txt
# rm -r TestText2.txt
# rm -r TestText3.txt
# rm -r $grepFile
# rm -r $s21_grepFile
# rm -r vgcore.*
