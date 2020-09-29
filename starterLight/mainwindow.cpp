#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>


/* **** début de la partie à compléter **** */
void MainWindow::get_carac(MyMesh* _mesh){
    qDebug() << "Nombre de sommets "<< _mesh->n_vertices();
    qDebug() << "Nombre de faces :" << _mesh->n_faces();
    qDebug() << "Is triangle" << _mesh->is_triangles();
}

bool MainWindow::test_lonely_face(MyMesh* _mesh){
    bool face_seule = true;

    for(MyMesh::FaceIter f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it){
        face_seule = true;
        for(MyMesh::FaceFaceIter ff_it = _mesh->ff_iter(*f_it); ff_it.is_valid(); ++ff_it) {
            face_seule = false;
        }
    }
    return face_seule;
}

bool MainWindow::test_lonely_vertex(MyMesh* _mesh){
    for(MyMesh::VertexIter v_it = _mesh->vertices_begin(); v_it != _mesh->vertices_end(); ++v_it){
        VertexHandle current_vertex = *v_it;
        if(_mesh->is_isolated(current_vertex)) return true;
    }
    return false;
}

bool MainWindow::test_lonely_edge(MyMesh* _mesh){
    for(MyMesh::EdgeIter e_it = _mesh->edges_begin(); e_it != _mesh->edges_end(); ++e_it){
        EdgeHandle current_edge = *e_it;
        HalfedgeHandle he1 = _mesh->halfedge_handle(current_edge, 0);
        HalfedgeHandle he2 = _mesh->halfedge_handle(current_edge, 1);
        if(!_mesh->face_handle(he1).is_valid() && !_mesh->face_handle(he2).is_valid()) return true;
    }
    return false;
}

//Calcule la normale d'une face
MyMesh::Normal MainWindow::face_norm(MyMesh *_mesh, MyMesh::FaceHandle face){
    return _mesh->calc_face_normal(face);
}

// Affiche la normale de toute les faces
void MainWindow::print_faces_norm(MyMesh *_mesh){
    MyMesh::Normal normal;
    for(MyMesh::FaceIter f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it){
        normal = face_norm(_mesh, *f_it);
        qDebug() << "Normale face n°" << f_it->idx() << " : " << normal[0] << "," << normal[1] << "," << normal[2];
    }
}

MyMesh::Normal MainWindow::vertex_norm(MyMesh *_mesh, MyMesh::VertexHandle vertex){
    int i=0;
    MyMesh::Normal normale;

    for(MyMesh::VertexFaceIter vf_it = _mesh->vf_iter(vertex); vf_it.is_valid(); ++vf_it){
        i++;
        FaceHandle face = *vf_it;
        MyMesh::Normal normal = face_norm(_mesh, face);
        normale[0] += normal[0]; normale[1] += normal[1]; normale[2] += normal[2];
    }
    normale[0] /= i; normale[1] /= i; normale[2] /= i;
    return normale;
}

void MainWindow::print_vertices_norm(MyMesh *_mesh){
    MyMesh::Normal normale;
    for(MyMesh::VertexIter v_it = _mesh->vertices_begin(); v_it != _mesh->vertices_end(); ++v_it){
        normale = vertex_norm(_mesh, *v_it);
        qDebug() << "Normale point n°" << v_it->idx() << " : " << normale[0] << "," << normale[1] << "," << normale[2];
    }
}

void MainWindow::ecart_angulaire(MyMesh* _mesh){
    MyMesh::Normal vertex_normal;
    MyMesh::Normal face_normal;
    float current_angle = 0;

    for(MyMesh::VertexIter v_it = _mesh->vertices_begin(); v_it != _mesh->vertices_end(); ++v_it){
        current_angle = 0;
        vertex_normal = vertex_norm(_mesh, *v_it);
        for(MyMesh::VertexFaceIter vf_it = _mesh->vf_iter(*v_it); vf_it.is_valid(); ++vf_it){
            face_normal = face_norm(_mesh, *vf_it);

            //Comparer ici la normale du vertex et celles des faces autours.
            //Calculer les angles entres la normale du points et de toutes ses faces adjacentes ==> mémoriser l'angle le plus grand parmi tous.
            float norm_Vertex_Normal = sqrt(pow(vertex_normal[0],2) + pow(vertex_normal[1],2) + pow(vertex_normal[2],2));
            float norm_Face_Normal = sqrt(pow(face_normal[0],2) + pow(face_normal[1],2) + pow(face_normal[2],2));
            float prod_scalaire = dot(vertex_normal,face_normal);

            /*u.v = ||u|| . ||v|| . cos(alpha)*/
            float new_angle = acos(prod_scalaire/(norm_Vertex_Normal*norm_Face_Normal));
            if(new_angle > current_angle) current_angle = new_angle;
        }
        _mesh->data(*v_it).value = current_angle;
    }
}

int MainWindow::nb_faces_isole(MyMesh* _mesh){
    bool face_seule = true;
    int nb_faces_seules = 0;

    for(MyMesh::FaceIter f_it = _mesh->faces_begin(); f_it != _mesh->faces_end(); ++f_it){
        face_seule = true;
        for(MyMesh::FaceFaceIter ff_it = _mesh->ff_iter(*f_it); ff_it.is_valid(); ++ff_it) {
            face_seule = false;
        }
        if(face_seule) nb_faces_seules++;
    }
    return nb_faces_seules;
}

int MainWindow::nb_points_isole(MyMesh* _mesh){
    int nb_points_seuls = 0;

    for(MyMesh::VertexIter v_it = _mesh->vertices_begin(); v_it != _mesh->vertices_end(); ++v_it){
        VertexHandle current_vertex = *v_it;
        if(_mesh->is_isolated(current_vertex)) nb_points_seuls++;
    }

    return nb_points_seuls;
}

int MainWindow::nb_aretes_isole(MyMesh* _mesh){
    int nb_aretes_seules = 0;

    for(MyMesh::EdgeIter e_it = _mesh->edges_begin(); e_it != _mesh->edges_end(); ++e_it){
        EdgeHandle current_edge = *e_it;
        HalfedgeHandle he1 = _mesh->halfedge_handle(current_edge, 0);
        HalfedgeHandle he2 = _mesh->halfedge_handle(current_edge, 1);
        if(!_mesh->face_handle(he1).is_valid() && !_mesh->face_handle(he2).is_valid()) nb_aretes_seules++;
    }
    return nb_aretes_seules;
}

/* **** fin de la partie à compléter **** */

/* **** début de la partie boutons et IHM **** */
void MainWindow::on_pushButton_Affiche_Carac_clicked(){
//   qDebug() << __FUNCTION__;
   get_carac(&mesh);
}

void MainWindow::on_pushButton_normales_faces_clicked(){
//    qDebug() << __FUNCTION__;
    print_faces_norm(&mesh);
}

void MainWindow::on_pushButton_normales_points_clicked(){
//    qDebug() << __FUNCTION__;
    print_vertices_norm(&mesh);
}

void MainWindow::on_pushButton_seuls_clicked(){
//    qDebug() << __FUNCTION__;
    qDebug() << "Face seule : " << test_lonely_face(&mesh) << ": il y a : " << nb_faces_isole(&mesh) << " faces seules";
    qDebug() << "Point seul : " << test_lonely_vertex(&mesh) << ": il y a : " << nb_points_isole(&mesh) << " points seuls";
    qDebug() << "Arete seule : " << test_lonely_edge(&mesh) << ": il y a : " << nb_aretes_isole(&mesh) << " aretes seules";
}

void MainWindow::on_pushButton_ecart_angulaire_clicked(){
    ecart_angulaire(&mesh);
    displayMesh(&mesh, DisplayMode::TemperatureMap);
}

void MainWindow::on_pushButton_H_clicked()
{
//    H_Curv(&mesh);
//    displayMesh(&mesh, DisplayMode::TemperatureMap); // permet de passer en mode "carte de temperatures", avec une gestion automatique de la couleur (voir exemple)
}

void MainWindow::on_pushButton_K_clicked()
{
//    K_Curv(&mesh);
//    displayMesh(&mesh, DisplayMode::TemperatureMap); // permet de passer en mode "carte de temperatures", avec une gestion automatique de la couleur (voir exemple)
}

/*  Cette fonction est à utiliser UNIQUEMENT avec le fichier testAngleArea.obj
    Elle est appelée par le bouton "Test angles/aires"

    Elle permet de vérifier les fonctions faceArea, angleFF et angleEE.
    Elle doit afficher :

    Aire de la face 0 : 2
    Aire de la face 1 : 2
    Angle entre les faces 0 et 1 : 1.5708
    Angle entre les faces 1 et 0 : -1.5708
    AngleEE au sommet 1 sur la face 0 : 0.785398 */
void MainWindow::on_pushButton_angleArea_clicked()
{

//    qDebug() << "Angle entre les faces 0 et 1 :" << angleFF(&mesh, 0, 1, 1, 2);
//    qDebug() << "Angle entre les faces 1 et 0 :" << angleFF(&mesh, 1, 0, 1, 2);

}

void MainWindow::on_pushButton_chargement_clicked()
{
    // fenêtre de sélection des fichiers
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Mesh"), "", tr("Mesh Files (*.obj)"));

    // chargement du fichier .obj dans la variable globale "mesh"
    OpenMesh::IO::read_mesh(mesh, fileName.toUtf8().constData());

    mesh.update_normals();

    // initialisation des couleurs et épaisseurs (sommets et arêtes) du mesh
    resetAllColorsAndThickness(&mesh);

    // on affiche le maillage
    displayMesh(&mesh);
}
/* **** fin de la partie boutons et IHM **** */

/* **** fonctions supplémentaires **** */
// permet d'initialiser les couleurs et les épaisseurs des élements du maillage
void MainWindow::resetAllColorsAndThickness(MyMesh* _mesh)
{
    for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
    {
        _mesh->data(*curVert).thickness = 1;
        _mesh->set_color(*curVert, MyMesh::Color(0, 0, 0));
    }

    for (MyMesh::FaceIter curFace = _mesh->faces_begin(); curFace != _mesh->faces_end(); curFace++)
    {
        _mesh->set_color(*curFace, MyMesh::Color(150, 150, 150));
    }

    for (MyMesh::EdgeIter curEdge = _mesh->edges_begin(); curEdge != _mesh->edges_end(); curEdge++)
    {
        _mesh->data(*curEdge).thickness = 1;
        _mesh->set_color(*curEdge, MyMesh::Color(0, 0, 0));
    }
}

// charge un objet MyMesh dans l'environnement OpenGL
void MainWindow::displayMesh(MyMesh* _mesh, DisplayMode mode)
{
    GLuint* triIndiceArray = new GLuint[_mesh->n_faces() * 3];
    GLfloat* triCols = new GLfloat[_mesh->n_faces() * 3 * 3];
    GLfloat* triVerts = new GLfloat[_mesh->n_faces() * 3 * 3];

    int i = 0;

    if(mode == DisplayMode::TemperatureMap)
    {
        QVector<float> values;
        for (MyMesh::VertexIter curVert = _mesh->vertices_begin(); curVert != _mesh->vertices_end(); curVert++)
            values.append(fabs(_mesh->data(*curVert).value));
        qSort(values);

        float range = values.at(values.size()*0.8);

        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;

        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            if(_mesh->data(*fvIt).value > 0){triCols[3*i+0] = 255; triCols[3*i+1] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+2] = 255 - std::min((_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            else{triCols[3*i+2] = 255; triCols[3*i+1] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0); triCols[3*i+0] = 255 - std::min((-_mesh->data(*fvIt).value/range) * 255.0, 255.0);}
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }

    if(mode == DisplayMode::Normal)
    {
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->color(*fIt)[0]; triCols[3*i+1] = _mesh->color(*fIt)[1]; triCols[3*i+2] = _mesh->color(*fIt)[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }

    if(mode == DisplayMode::ColorShading)
    {
        MyMesh::ConstFaceIter fIt(_mesh->faces_begin()), fEnd(_mesh->faces_end());
        MyMesh::ConstFaceVertexIter fvIt;
        for (; fIt!=fEnd; ++fIt)
        {
            fvIt = _mesh->cfv_iter(*fIt);
            triCols[3*i+0] = _mesh->data(*fvIt).faceShadingColor[0]; triCols[3*i+1] = _mesh->data(*fvIt).faceShadingColor[1]; triCols[3*i+2] = _mesh->data(*fvIt).faceShadingColor[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->data(*fvIt).faceShadingColor[0]; triCols[3*i+1] = _mesh->data(*fvIt).faceShadingColor[1]; triCols[3*i+2] = _mesh->data(*fvIt).faceShadingColor[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++; ++fvIt;
            triCols[3*i+0] = _mesh->data(*fvIt).faceShadingColor[0]; triCols[3*i+1] = _mesh->data(*fvIt).faceShadingColor[1]; triCols[3*i+2] = _mesh->data(*fvIt).faceShadingColor[2];
            triVerts[3*i+0] = _mesh->point(*fvIt)[0]; triVerts[3*i+1] = _mesh->point(*fvIt)[1]; triVerts[3*i+2] = _mesh->point(*fvIt)[2];
            triIndiceArray[i] = i;

            i++;
        }
    }


    ui->displayWidget->loadMesh(triVerts, triCols, _mesh->n_faces() * 3 * 3, triIndiceArray, _mesh->n_faces() * 3);

    delete[] triIndiceArray;
    delete[] triCols;
    delete[] triVerts;

    GLuint* linesIndiceArray = new GLuint[_mesh->n_edges() * 2];
    GLfloat* linesCols = new GLfloat[_mesh->n_edges() * 2 * 3];
    GLfloat* linesVerts = new GLfloat[_mesh->n_edges() * 2 * 3];

    i = 0;
    QHash<float, QList<int> > edgesIDbyThickness;
    for (MyMesh::EdgeIter eit = _mesh->edges_begin(); eit != _mesh->edges_end(); ++eit)
    {
        float t = _mesh->data(*eit).thickness;
        if(t > 0)
        {
            if(!edgesIDbyThickness.contains(t))
                edgesIDbyThickness[t] = QList<int>();
            edgesIDbyThickness[t].append((*eit).idx());
        }
    }
    QHashIterator<float, QList<int> > it(edgesIDbyThickness);
    QList<QPair<float, int> > edgeSizes;
    while (it.hasNext())
    {
        it.next();

        for(int e = 0; e < it.value().size(); e++)
        {
            int eidx = it.value().at(e);

            MyMesh::VertexHandle vh1 = _mesh->to_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh1)[0];
            linesVerts[3*i+1] = _mesh->point(vh1)[1];
            linesVerts[3*i+2] = _mesh->point(vh1)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;

            MyMesh::VertexHandle vh2 = _mesh->from_vertex_handle(_mesh->halfedge_handle(_mesh->edge_handle(eidx), 0));
            linesVerts[3*i+0] = _mesh->point(vh2)[0];
            linesVerts[3*i+1] = _mesh->point(vh2)[1];
            linesVerts[3*i+2] = _mesh->point(vh2)[2];
            linesCols[3*i+0] = _mesh->color(_mesh->edge_handle(eidx))[0];
            linesCols[3*i+1] = _mesh->color(_mesh->edge_handle(eidx))[1];
            linesCols[3*i+2] = _mesh->color(_mesh->edge_handle(eidx))[2];
            linesIndiceArray[i] = i;
            i++;
        }
        edgeSizes.append(qMakePair(it.key(), it.value().size()));
    }

    ui->displayWidget->loadLines(linesVerts, linesCols, i * 3, linesIndiceArray, i, edgeSizes);

    delete[] linesIndiceArray;
    delete[] linesCols;
    delete[] linesVerts;

    GLuint* pointsIndiceArray = new GLuint[_mesh->n_vertices()];
    GLfloat* pointsCols = new GLfloat[_mesh->n_vertices() * 3];
    GLfloat* pointsVerts = new GLfloat[_mesh->n_vertices() * 3];

    i = 0;
    QHash<float, QList<int> > vertsIDbyThickness;
    for (MyMesh::VertexIter vit = _mesh->vertices_begin(); vit != _mesh->vertices_end(); ++vit)
    {
        float t = _mesh->data(*vit).thickness;
        if(t > 0)
        {
            if(!vertsIDbyThickness.contains(t))
                vertsIDbyThickness[t] = QList<int>();
            vertsIDbyThickness[t].append((*vit).idx());
        }
    }
    QHashIterator<float, QList<int> > vitt(vertsIDbyThickness);
    QList<QPair<float, int> > vertsSizes;

    while (vitt.hasNext())
    {
        vitt.next();

        for(int v = 0; v < vitt.value().size(); v++)
        {
            int vidx = vitt.value().at(v);

            pointsVerts[3*i+0] = _mesh->point(_mesh->vertex_handle(vidx))[0];
            pointsVerts[3*i+1] = _mesh->point(_mesh->vertex_handle(vidx))[1];
            pointsVerts[3*i+2] = _mesh->point(_mesh->vertex_handle(vidx))[2];
            pointsCols[3*i+0] = _mesh->color(_mesh->vertex_handle(vidx))[0];
            pointsCols[3*i+1] = _mesh->color(_mesh->vertex_handle(vidx))[1];
            pointsCols[3*i+2] = _mesh->color(_mesh->vertex_handle(vidx))[2];
            pointsIndiceArray[i] = i;
            i++;
        }
        vertsSizes.append(qMakePair(vitt.key(), vitt.value().size()));
    }

    ui->displayWidget->loadPoints(pointsVerts, pointsCols, i * 3, pointsIndiceArray, i, vertsSizes);

    delete[] pointsIndiceArray;
    delete[] pointsCols;
    delete[] pointsVerts;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    vertexSelection = -1;
    edgeSelection = -1;
    faceSelection = -1;

    modevoisinage = false;

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
