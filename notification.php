<?php 


if ($_SERVER['REQUEST_METHOD'] === 'POST'){
	
	
	$motionStatus = $_POST['motion_status'];
    
    file_put_contents('motion_status.txt', $motionStatus);

    
    echo 'Notification received';
	
	
	
}

?>