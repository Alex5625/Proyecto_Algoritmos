import gi
import csv

gi.require_version('Gtk', '4.0')
from gi.repository import Gtk, Gio, GObject, GdkPixbuf

APPID = 'com.example.liststore'


class Row(GObject.Object):
    def __init__(self, *data):
        super().__init__()
        self.data = data


class Gtk4TestTest(Gtk.ApplicationWindow):
    def __init__(self, app):
        super().__init__(application=app, title='Visualización Alineación')

        # Leer matriz desde archivo CSV
        self.matriz = self.leer_csv('matriz_gtk.csv')

        if not self.matriz:
            print("El archivo CSV está vacío o no se pudo leer.")
            self.matriz = [["No hay datos"]]  # Valor por defecto en caso de error

        self.filas = self.leer_secuencia("cad1.tex")
        self.columnas = self.leer_secuencia("cad2.tex")

        print(f"filas: {self.filas}")
        print(f"Columnas: {self.columnas}")
        # Agregar nombres a las filas como primera columna
        self.matriz = [[f"{self.filas[i]}"] + fila for i, fila in enumerate(self.matriz)]

        # Crear el contenedor principal
        vbox = Gtk.Box(orientation=Gtk.Orientation.VERTICAL, spacing=10)
        self.set_child(vbox)



        # Crear ColumnView para mostrar la matriz
        self.columnview = Gtk.ColumnView()
        vbox.append(self.columnview)

        # Crear modelo para los datos
        self.model = Gio.ListStore()
        for fila in self.matriz:
            self.model.append(Row(*fila))

        # Configurar datos en ColumnView
        smodel = Gtk.SingleSelection(model=self.model)
        self.columnview.set_model(smodel)
        self.crear_columnas(len(self.matriz[0]), self.columnas)



    def leer_csv(self, nombreArchivo):
        """
        Lee una matriz desde un archivo CSV y la retorna como lista de listas.
        """
        matriz = []
        try:
            with open(nombreArchivo, newline='') as archivo_csv:
                lector_csv = csv.reader(archivo_csv)
                for fila in lector_csv:
                    matriz.append(fila)  # Agregar cada fila como lista
        except FileNotFoundError:
            print(f"Error: El archivo {nombreArchivo} no se encontró.")
        except Exception as e:
            print(f"Error al leer el archivo: {e}")
        return matriz

    def crear_columnas(self, num_columnas, columnas):
        """
        Crea las columnas dinámicamente en el ColumnView.
        """
        for i in range(num_columnas):
            factory = Gtk.SignalListItemFactory()
            factory.connect("setup", self.on_list_item_setup)
            factory.connect("bind", self.on_list_item_bind, i)

            # La primera columna será estática y mostrará los nombres de las filas
            if i == 0:
                column_title = ""
            elif i == 1:
                column_title = "-"
            else:
                columna_title = f"{self.columnas[i-1]}"

            column = Gtk.ColumnViewColumn(
                title=column_title,
                factory=factory,
            )
            column.set_resizable(True)
            column.set_expand(True)
            self.columnview.append_column(column)

    def leer_secuencia(self, nombreArchivo):
        with open(nombreArchivo, 'r') as archivo:
            secuencia = archivo.read().strip()
            return secuencia

    def on_list_item_setup(self, factory, list_item):
        """
        Configura cada celda del ColumnView.
        """
        label = Gtk.Inscription()
        list_item.set_child(label)

    def on_list_item_bind(self, factory, list_item, columna_index):
        """
        Asigna el valor correspondiente a cada celda.
        """
        row = list_item.get_item()
        list_item.get_child().set_text(str(row.data[columna_index]))


class Gtk4TestApp(Gtk.Application):
    def __init__(self):
        super().__init__(application_id=APPID)

    def do_activate(self):
        window = Gtk4TestTest(self)
        window.present()


def main():
    app = Gtk4TestApp()
    app.run()


if __name__ == '__main__':
    main()