#include <iostream>
#include <fstream>
#include <list> 
#include <string>
#include <algorithm>

// Se crea una función para obtener la IP de una línea
std::string obtenerIP(const std::string &linea)
{
    size_t inicio = linea.find(' ', 15) + 1;   // Se encuentra el espacio después del carácter 15
    size_t fin = linea.find(':', inicio);      // Se encuentra el carácter ':'
    return linea.substr(inicio, fin - inicio); // Extraemos la IP
}

// Se crea una función para comparar las IPs y ordenar las líneas del archivo
bool compararIPs(const std::string &linea1, const std::string &linea2)
{
    std::string ip1 = obtenerIP(linea1);
    std::string ip2 = obtenerIP(linea2);
    return ip1 < ip2; // Comparación
}

// Se crea una función para convertir una IP en un número para hacer más fácil la comparación
unsigned long convertirIP(const std::string &ip)
{
    unsigned long resultado = 0;
    int partes[4];
    sscanf(ip.c_str(), "%d.%d.%d.%d", &partes[0], &partes[1], &partes[2], &partes[3]);
    resultado = (partes[0] << 24) | (partes[1] << 16) | (partes[2] << 8) | partes[3];
    return resultado;
}

int main()
{
    // Se crea una lista doblemente ligada para guardar los datos del archivo "bitacora.txt" en lugar de un vector.
    std::list<std::string> datos;

    // Abre el archivo "bitacora.txt"
    std::ifstream archivo("bitacora.txt");
    if (!archivo.is_open())
    {
        std::cerr << "No se pudo abrir el archivo correctamente." << std::endl;
        return 1;
    }

    // Lee línea por línea el archivo y guarda los datos en la lista
    std::string linea;
    while (std::getline(archivo, linea))
    {
        datos.push_back(linea);
    }
    archivo.close(); // Cierra el archivo

    // Ordena los datos por IP usando la función compararIPs
    datos.sort(compararIPs); 

    // Crear un archivo de salida para guardar los datos ordenados
    std::ofstream archivoSalida("bitacora_ordenada_por_ip.txt");
    if (!archivoSalida.is_open())
    {
        std::cerr << "No se pudo crear el archivo de salida." << std::endl;
        return 1;
    }

    // Escribir todos los registros ordenados en el archivo de salida
    for (const auto &registro : datos)
    {
        archivoSalida << registro << std::endl;
    }
    archivoSalida.close();

    // Solicita al usuario las IPs de inicio y fin de búsqueda
    std::string ipInicio, ipFin;
    std::cout << "Ingrese la IP de inicio (formato XXX.XXX.XXX.XXX): ";
    std::getline(std::cin, ipInicio);
    std::cout << "Ingrese la IP de fin (formato XXX.XXX.XXX.XXX): ";
    std::getline(std::cin, ipFin);

    // Convierte las IPs que se ingresaron a numero
    unsigned long ipInicioNum = convertirIP(ipInicio);
    unsigned long ipFinNum = convertirIP(ipFin);

    // Muestra los registros que están dentro del rango de IPs ingresadas por el usuario
    bool registrosEncontrados = false;
    for (const auto &registro : datos)
    {
        std::string ip = obtenerIP(registro);
        unsigned long ipNum = convertirIP(ip);
        if (ipNum >= ipInicioNum && ipNum <= ipFinNum)
        {
            std::cout << registro << std::endl; // Imprime los registros en pantalla
            registrosEncontrados = true;
        }
    }

    if (!registrosEncontrados)
    {
        std::cout << "No se encontraron registros en el rango de IPs proporcionado. Intenta de nuevo." << std::endl;
    }

    std::cout << "Los registros se han organizado y guardado en 'bitacora_ordenada_por_ip.txt'." << std::endl;

    return 0;
}
