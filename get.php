<?php

require 'database.php';

try {
    $query = $conn->query('SELECT id, umidade, temperatura FROM logs_temperatura ORDER BY id DESC LIMIT 200'); // 200 ultimos ID QUE SERÃO MOSTRADOS NO GRÁFICO
    $data = $query->fetchAll(PDO::FETCH_ASSOC);
    header('Content-Type: application/json');
    echo json_encode($data);
} catch(PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>
