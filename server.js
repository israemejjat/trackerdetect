


const express = require('express');
const app = express();

app.use(express.json());

let currentPosition = { latitude: null, longitude: null };

let positionHistory = [
    { latitude: 33.225536, longitude: -8.488316, time: '2025-01-10 14:00' },
    { latitude: 33.224500, longitude: -8.489500, time: '2025-01-09 14:30' },
    { latitude: 33.223000, longitude: -8.490000, time: '2025-01-08 14:15' }
];

app.get('/', (req, res) => {
    res.sendFile(__dirname + '/public/index.html');
});

app.post('/send-data', (req, res) => {
    const { latitude, longitude } = req.body;

    if (latitude && longitude) {
        currentPosition = { latitude, longitude }; 
        console.log(`Position reçue : Latitude = ${latitude}, Longitude = ${longitude}`);
        res.status(200).send('Données reçues avec succès');
    } else {
        console.log('Données GPS manquantes');
        res.status(400).send('Erreur : données GPS manquantes');
    }
});

app.get('/current-position', (req, res) => {
    if (currentPosition.latitude && currentPosition.longitude) {
        res.json(currentPosition); 
    } else {
        const lastPosition = positionHistory[positionHistory.length - 1];
        res.json(lastPosition);
    }
});

app.use(express.static('public'));

const PORT = 3000;
app.listen(PORT, () => {
    console.log(`Serveur en cours d'exécution sur http://localhost:${PORT}`);
});
