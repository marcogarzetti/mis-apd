

float DenormalizeParam(float value, float rangeMin, float rangeMax)
{
	return (value * (rangeMax - rangeMin)) + rangeMin;
}

float NormalizeParam(float value, float rangeMin, float rangeMax)
{
	return (value - rangeMin) * (rangeMax - rangeMin);
}