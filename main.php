<?php
    $temperatura = $_GET['temperatura'];
    $umidade = $_GET['umidade'];

	$hostname="localhost";
	$username="root";
	$password="";
	$dbname="test";
	
	$conn = new mysqli($hostname,$username, $password, $dbname);

    //pegar data de hoje 
    $agora =  date('Y-m-d H:i:s');

	//inserir dados no banco
    $sql = "INSERT INTO CHANGE_THIS_TABLE_NAME SET temperatura='$temperatura', umidade='$umidade' , created_at = '$agora' ";   //ALTERAR O NOME DA TABELA

    //Código para debugar erros na query caso necessário
 //    if ( $conn->query($sql) === TRUE) {
 //        echo "New record created successfully";
 //      } else {
 //        echo "Error: " . $sql . "<br>" . mysqli_error($conn);
 //     }

?>
