for i in {0..6}
do
  ./app ./test_cases/input$i.txt ./my_outputs/out$i.txt
  diff ./test_cases/output$i.txt ./my_outputs/out$i.txt
done