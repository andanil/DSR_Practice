var map;
function initMap() {
	var options = {
        zoom:3,
        center:{lat:12.61,lng:35.63}
	}
	map = new google.maps.Map(document.getElementById('map'), options);
}

function getCoords(user)
{
	var latitude = user.Latitude / 100;
	if(user.NorthOrSouth == "S")
		latitude *= -1;
	var longitude = user.Longitude / 100;
	if(user.WestOrEast == "W")
		longitude *= -1;
	return {lat:latitude,lng:longitude};
}

function getDate(user)
{
	return user.Date.slice(0,2) + '.' + user.Date.slice(2,4) + '.' + user.Date.slice(4,6) + ' ' +  user.Time.slice(0,2) + ':' + 
user.Time.slice(2,4) + ':' + user.Time.slice(4,6);
}

function getContent(user)
{
	return '<h3>' + user.Login + '</h3>' + '<p>Date: ' + getDate(user) + '</p>';
}

function addMarker(props)
{
	var marker = new google.maps.Marker({ position:props.coords, map:map});

	if(props.content)
	{
		var infoWindow = new google.maps.InfoWindow({content:props.content});
		marker.addListener('click', function(){ infoWindow.open(map, marker); }); 
	}
}

function viewData(data)
{
	var users = JSON.parse(data);
	for(var i = 0; i < users.length; i++)
	{
		addMarker({coords:getCoords(users[i]), content:getContent(users[i])});
	}
}