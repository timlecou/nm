nm $@ > off
./ft_nm $@ > mine
diff -u off mine
#rm off mine
