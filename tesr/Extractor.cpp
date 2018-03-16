//
//  Extractor.cpp
//  tesr
//
//  Created by Micheli  Knechtel on 28/04/2016.
//  Copyright © 2016 Micheli Knechtel. All rights reserved.
//

#include "Extractor.hpp"
#include <map>

void  Extractor::getMatrixBlock(IloCplex cplex)
{
    getGroup(cplex);
    printGroup();
    buildMatrix();
}


//void Extractor::buildMatrix()
//{
//    map<string,clusterGroup>::iterator it = group.begin();
//    
//    std::map<string,clusterGroup>::iterator itAux = group.begin();
//    cout<<endl;
//    string blockMatriz = "Matrix Block\n\n";
//    blockMatriz +="   ";
//    
//    if (networkSize<9)
//    {
//        for (it=group.begin(); it!=group.end(); ++it)
//        {
//            clusterGroup g = it->second;
//            if (g.size == 0)
//            {
//                blockMatriz +="E ";
//            }
//            else
//            {
//                for (int i = 0; i<g.size; i++)
//                {
//                    blockMatriz += DataManager::getDataManager()->nodeID2Name.at(DataManager::getDataManager()->index2ID.at(g.elements[i]));//SSTRL(g.elements[i]);
//                    if (g.size-1==i)
//                    {
//                        blockMatriz+=" ";
//                    }
//                }
//            }
//        }
//    }
//    
//    blockMatriz+="\n";
//    for (it=group.begin(); it!=group.end(); ++it)
//    {
//        clusterGroup g = it->second;
//        if (g.size == 0)
//        {
//            for (int i = 0; i<1; i++)
//            {
//                itAux = group.begin();
//                blockMatriz += " ";
//                blockMatriz.append(17  ,'.');
//                
//                for(int k = 0; k<clusterUpperBound; k++)
//                {
//                    if (clusterUpperBound!=1)
//                        blockMatriz+=" ";
//                    clusterGroup gAux = itAux->second;
//                    if (gAux.size ==0)
//                    {
//                        blockMatriz += "-";
//                    }
//                    for (int l = 0; l<gAux.size; l++)
//                    {
//                        if (clusterUpperBound==1 && l == 0)
//                            blockMatriz+=" ";
//                        
//                        blockMatriz += "-";
//                    }
//                    itAux++;
//                }
//            }
//        }
//        for (int i = 0; i<g.size; i++)
//        {
//            itAux = group.begin();
//            string verticeName = DataManager::getDataManager()->nodeID2Name.at(DataManager::getDataManager()->index2ID.at(g.elements[i]));
//            blockMatriz += " " + verticeName;
//            int n = 17 - verticeName.length();
//            blockMatriz.append(n  ,'.');
//
//            for(int k = 0; k<clusterUpperBound; k++)
//            {
//                if (clusterUpperBound!=1)
//                    blockMatriz+=" ";
//                
//                clusterGroup gAux = itAux->second;
//                
//                if (gAux.size ==0)
//                {
//                    blockMatriz += "-";
//                }
//                
//                for (int l = 0; l<gAux.size; l++)
//                {
//                    if (clusterUpperBound==1 && l == 0)
//                        blockMatriz+=" ";
//                    
//                    blockMatriz +=SSTRL(relationMatrix[g.elements[i]][gAux.elements[l]]);
//                    LOG("relationMatrix ["+SSTRL(g.elements[i])+"]["+SSTRL(gAux.elements[l])+"]="+SSTRL(relationMatrix[g.elements[i]][gAux.elements[l]]));
//                }
//                if (clusterUpperBound==1)
//                    blockMatriz+="\n";
//                itAux++;
//            }
//            if (g.size-1!=i && clusterUpperBound!=1)
//                blockMatriz+="\n";
//        }
//        if (clusterUpperBound!=1)
//            blockMatriz+="\n\n";
//    }
//    cout<<blockMatriz;
//}
//
//

void Extractor::buildMatrix()
{
    map<string,clusterGroup>::iterator it = group.begin();

    std::map<string,clusterGroup>::iterator itAux = group.begin();
    cout<<endl;
    string blockMatriz = " Matrix Block\n\n";
    blockMatriz +="   ";

    if (networkSize<9)
    {
        for (it=group.begin(); it!=group.end(); ++it)
        {
            clusterGroup g = it->second;

            if (g.size == 0)
            {
                blockMatriz +="E ";
            }
            else
            {
                for (int i = 0; i<g.size; i++)
                {
                    if (DataManager::getDataManager()->matrixDataType==XML)
                        blockMatriz += DataManager::getDataManager()->nodeID2Name.at(DataManager::getDataManager()->index2ID.at(g.elements[i]));
                    else
                        blockMatriz +=SSTRL(g.elements[i]);
                   
                    if (g.size-1==i)
                        blockMatriz+=" ";
                }
            }
        }
    }

    blockMatriz+="\n";
    
    for (it=group.begin(); it!=group.end(); ++it)
    {
        clusterGroup g = it->second;
        if (g.size == 0)
        {
            for (int i = 0; i<1; i++)
            {
                itAux = group.begin();
                if (DataManager::getDataManager()->matrixDataType==XML)
                {
                    blockMatriz += " ";
                    blockMatriz.append(DataManager::getDataManager()->verticeLabelMaxSize ,'.');
                }
                else
                    blockMatriz += " E";
               
                if (DataManager::getDataManager()->matrixDataType!=XML)
                    if (networkSize>9)
                        blockMatriz += " ";

                for(int k = 0; k<clusterUpperBound; k++)
                {
                    if (clusterUpperBound!=1)
                        blockMatriz+=" ";
                    
                    clusterGroup gAux = itAux->second;
                    
                    if (gAux.size ==0)
                    {
                        blockMatriz += "-";
                    }
                    
                    for (int l = 0; l<gAux.size; l++)
                    {
                        if (clusterUpperBound==1 && l == 0)
                            blockMatriz+=" ";

                        blockMatriz += "-";
                    }
                    itAux++;
                }
            }
        }
        for (int i = 0; i<g.size; i++)
        {
            itAux = group.begin();
            if (DataManager::getDataManager()->matrixDataType==XML)
            {
                string verticeName = DataManager::getDataManager()->nodeID2Name.at(DataManager::getDataManager()->index2ID.at(g.elements[i]));
                blockMatriz += " " + verticeName;
                blockMatriz.append(DataManager::getDataManager()->verticeLabelMaxSize - (int) verticeName.length()  ,'.');
            }
            else
                blockMatriz += " " +SSTRL(g.elements[i]);

            // Mal implementado, refazer !!!
            if (DataManager::getDataManager()->matrixDataType!=XML)
                if (g.elements[i]<10 && networkSize>9)
                    blockMatriz += " ";

            for(int k = 0; k<clusterUpperBound; k++)
            {
                if (clusterUpperBound!=1)
                    blockMatriz+=" ";

                clusterGroup gAux = itAux->second;

                if (gAux.size ==0)
                {
                    blockMatriz += "-";
                }

                for (int l = 0; l<gAux.size; l++)
                {
                    if (clusterUpperBound==1 && l == 0)
                        blockMatriz+=" ";

                    blockMatriz +=SSTRL(relationMatrix[g.elements[i]][gAux.elements[l]]);
                    LOG("relationMatrix ["+SSTRL(g.elements[i])+"]["+SSTRL(gAux.elements[l])+"]="+SSTRL(relationMatrix[g.elements[i]][gAux.elements[l]]));
                }
                if (clusterUpperBound==1)
                    blockMatriz+="\n";
                itAux++;
            }
            if (g.size-1!=i && clusterUpperBound!=1)
                blockMatriz+="\n";
        }
        if (clusterUpperBound!=1)
            blockMatriz+="\n\n";
    }
    cout<<blockMatriz;
}


void  Extractor::getGroup(IloCplex cplex)
{
    
    if (group.size()>0)
        return;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        string clusterName= "C" + SSTRL(k);
        int *elements = (int *) malloc(networkSize*sizeof(int));
        int size = 0;
        
        for (int i = k; i<networkSize; i++)
        {
            if (cplex.isExtracted(x[i][k]))
            {
                int  value = cplex.getValue(x[i][k]);
                
                if(value > 0.9)
                {
                    elements[size] = i;
                    size++;
                    LOG(value);
                }
                
            }
            
        }
        clusterGroup g;
        g.elements = elements;
        g.size = size;
        group.insert(pair<string, clusterGroup>(clusterName,g));
    }
}

void Extractor::printGroup()
{
    
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    if (DataManager::getDataManager()->matrixDataType==XML)
    {
        for (it=group.begin(); it!=group.end(); ++it)
        {
            cout<<it->first<<" = \t{";
            clusterGroup g = it->second;
            for (int i = 0; i<g.size; i++)
            {
                string verticeLabel = DataManager::getDataManager()->nodeID2Name.at(DataManager::getDataManager()->index2ID.at(g.elements[i]));
                
                if ((i==0 && g.size ==1) || i == g.size-1)
                {
                    cout<<"("<<verticeLabel<<")";
                }
                else
                {
                    cout<<"("<<verticeLabel<<")"<<",";
                }
            }
            cout<<"};"<<endl;
        }
    }
    else
    {
        for (it=group.begin(); it!=group.end(); ++it)
        {
            cout<<it->first<<" = {";
            clusterGroup g = it->second;
            for (int i = 0; i<g.size; i++)
            {
                if ((i==0 && g.size ==1) || i == g.size-1)
                    cout<<"("<<g.elements[i]<<")";
                else
                    cout<<"("<<g.elements[i]<<")"<<",";
            }
            cout<<"}"<<endl;
        }
    }
}

void Extractor::get_x(IloCplex cplex)
{
    cout<<endl;
    
    for (int i = 0; i<networkSize; i++)
    {
                for (int k = 0; k<=min(clusterUpperBound-1, i); k++)
//        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (cplex.isExtracted(x[i][k]))
                cout<<"x("<<i<<")("<<k<<") = "<<cplex.getValue(x[i][k])<<endl;
            else
                cout<<"x("<<i<<")("<<k<<") =  was not add to the model !!!"<<endl;
        }
    }
    cout<<endl;
    
}

void Extractor::get_tbsOne(IloCplex cplex)
{
    cout<<endl;
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if(itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            
            if (cplex.isExtracted(tbsOne[k][l]))
                cout<<"tbsOne("<<k<<")("<<l<<") = "<<cplex.getValue(tbsOne[k][l])<<endl;
            else
                cout<<"tbsOne("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
        }
    }
    cout<<endl;
}

void Extractor::get_tbsZero(IloCplex cplex)
{
    cout<<endl;
    int limit = clusterUpperBound-1;
    
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if(itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            if (cplex.isExtracted(tbsZero[k][l]))
                cout<<"tbsZero("<<k<<")("<<l<<") = "<<cplex.getValue(tbsZero[k][l])<<endl;
            else
                cout<<"tbsZero("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
        }
    }
    cout<<endl;
}

void Extractor::getRelationMatrix()
{
    cout<<endl;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            cout<<"relationMatrix("<<k<<")("<<l<<")"<<relationMatrix[k][l]<<endl;
        }
    }
    cout<<endl;
}

void Extractor::get_y(IloCplex cplex)
{
    cout<<endl;
    for (int i = 0; i<networkSize; i++)
    {
        for (int j = 0; j<networkSize; j++)
        {
            for (int k = 0; k<clusterUpperBound; k++)
            {
                for (int l = 0; l<clusterUpperBound; l++)
                {
                    if (cplex.isExtracted(y[i][j][k][l]))
                        cout<<"y("<<i<<")("<<j<<")"<<"("<<k<<")"<<"("<<l<<") = "<<cplex.getValue(y[i][j][k][l])<<endl;
                    else
                        cout<<"y("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
                }
            }
        }
    }
    cout<<endl;
}

void Extractor::get_dsZero(IloCplex cplex)
{
    cout<<endl;
    
    if (!DataManager::getDataManager()->areThereBlockWithDiagonalVariationZero())
        return;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (!DataManager::getDataManager()->areThereBlockWithDiagonalVariationOne())
            return;
        
        if (cplex.isExtracted(dsZero[k][0]))
            cout<<"dsZero("<<k<<")("<<k<<") = "<<cplex.getValue(dsZero[k][0])<<endl;
        else
            cout<<"dsZero("<<k<<")("<<k<<") =  was not add to the model !!!"<<endl;
        
    }
    cout<<endl;
}

void Extractor::get_dsOne(IloCplex cplex)
{
    cout<<endl;
    
    if (!DataManager::getDataManager()->areThereBlockWithDiagonalVariationOne())
        return;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (!DataManager::getDataManager()->areThereBlockWithDiagonalVariationOne())
            return;
        
        if (cplex.isExtracted(dsOne[k][0]))
            cout<<"dsOne("<<k<<")("<<k<<") = "<<cplex.getValue(dsOne[k][0])<<endl;
        else
            cout<<"dsOne("<<k<<")("<<k<<") =  was not add to the model !!!"<<endl;
        
    }
    cout<<endl;
}

void Extractor::get_bSize(IloCplex cplex)
{
    cout<<endl;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if (cplex.isExtracted(bSize[k][l]))
                cout<<"bSize("<<k<<")("<<l<<") = "<<cplex.getValue(bSize[k][l])<<endl;
            else
                cout<<"bSize("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
        }
    }
    cout<<endl;
}

void  Extractor::get_w(IloCplex cplex)
{
    int limit = clusterUpperBound-1;
    
    for(int i=0; i <DataManager::getDataManager()->functionSize; i++)
    {
        
        FunctionRelease release = DataManager::getDataManager()->functionMapping[i].release;
        
        
        for(int j=0; j <DataManager::getDataManager()->clusterUpperBound; j++)
        {
            if (release == DIAGONAL)
            {
                get_fIndex(i);
                if (cplex.isExtracted(w[i][j][0]))
                {
                    
                    cout<<"w("<<i<<")("<<j<<")("<<j<<") = "<<cplex.getValue(w[i][j][0])<<endl;
                }
                else
                    cout<<"w("<<i<<")("<<j<<")("<<j<<") = was not add to the model !!!"<<endl;
            }
            else
            {
                if (itsSymmetricGraph && !DataManager::getDataManager()->areThereNonSymmetricPropertie())
                    limit = j;
                
                for(int k=0; k<=limit; k++)
                {
                    get_fIndex(i);
                    
                    if (cplex.isExtracted(w[i][j][k]))
                    {
                        cout<<"w("<<i<<")("<<j<<")("<<k<<") = "<<cplex.getValue(w[i][j][k])<<endl;
                    }
                    else
                    {
                        cout<<"w("<<i<<")("<<j<<")("<<k<<") = was not add to the model !!!"<<endl;
                    }
                    
                }
            }
            
        }
    }
    
    
}

void  Extractor::get_rowError(IloCplex cplex)
{
    cout<<endl;
    
    
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if(itsSymmetricGraph)
            limit = k;
        int sum=0;
        for (int l = 0; l<=limit; l++)
        {
            for (int p = 0; p<networkSize; p++)
            {
                if (cplex.isExtracted(rowError[p][k][l]))
                {
                    sum+=cplex.getValue(rowError[p][k][l]);
                    //                    cout<<"rowError("<<p<<")("<<k<<")("<<l<<") = "<<cplex.getValue(rowError[p][k][l])<<endl;
                }
                else
                    cout<<"rowError("<<p<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
            }
            cout<<"rowError("<<k<<")("<<l<<") = "<<sum<<endl;
            //             cout<<endl;
        }
    }
    cout<<endl;
}

void  Extractor::get_colError(IloCplex cplex)
{
    cout<<endl;
    int limit = clusterUpperBound-1;
    
    //    if (!DataManager::getDataManager()->isTypeAdded(CRB))
    //          return;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if(itsSymmetricGraph)
            limit = k;
        int sum=0;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int p = 0; p<networkSize; p++)
            {
                if (cplex.isExtracted(colError[p][k][l])){
                    sum+=cplex.getValue(colError[p][k][l]);
                    
                    //                    cout<<"colError("<<p<<")("<<k<<")("<<l<<") = "<<cplex.getValue(colError[p][k][l])<<endl;
                }
                else
                    cout<<"colError("<<p<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
            }
            cout<<"colError("<<k<<")("<<l<<") = "<<sum<<endl;
            
            //            cout<<endl;
        }
    }
    cout<<endl;
}


void  Extractor::get_emptyCluster(IloCplex cplex)
{
    cout<<endl;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (cplex.isExtracted(emptyCluster[k]))
        {
            cout<<"emptyCluster("<<k<<")= "<<cplex.getValue(emptyCluster[k])<<endl;
        }
        else
            cout<<"emptyCluster("<<k<<")=   was not add to the model !!!"<<endl;
        
    }
    cout<<endl;
}


void  Extractor::get_f(IloCplex cplex)
{
    cout<<endl;
    
    int limit = clusterUpperBound-1;
    
    for(int i=0; i <DataManager::getDataManager()->functionSize; i++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[i].release;
        
        for (int k = 0; k<clusterUpperBound; k++)
        {
            if (itsSymmetricGraph &&  !DataManager::getDataManager()->areThereNonSymmetricPropertie())
                limit = k;
            
            for (int l = 0; l<=limit; l++)
            {
                if (release==DIAGONAL)
                {
                    if (k==l)
                    {
                        if (cplex.isExtracted(f[i][k][0]))
                        {
                            get_fIndex(i);
                            cout<<"f("<<i<<")("<<k<<")("<<l<<") = "<<cplex.getValue(f[i][k][0])<<endl;
                        }
                        else
                        {
                            get_fIndex(i);
                            cout<<"f("<<i<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
                        }
                    }
                    
                }
                else
                {
                    if (cplex.isExtracted(f[i][k][l]))
                    {
                        get_fIndex(i);
                        cout<<"f("<<i<<")("<<k<<")("<<l<<") = "<<cplex.getValue(f[i][k][l])<<endl;
                    }
                    else
                    {
                        get_fIndex(i);
                        cout<<"f("<<i<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
                    }
                }
            }
        }
    }
    cout<<endl;
}

void Extractor::get_NullBlockDiagonalZero(IloCplex cplex)
{
    cout<<endl;
    cout<<"NullBlock with diagonal equals zero "<<endl;
    cout<<"Desviation Measuare = block error + diagonal error;"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsOne[k][l]) && cplex.isExtracted(dsOne[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<" + "<<"-"<<" = - "<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsOne[k][l]) && cplex.isExtracted(dsOne[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<<cplex.getValue(tbsOne[k][l])<<" + "<<cplex.getValue(dsOne[k][l])<<" = "<< cplex.getValue(tbsOne[k][l])+ cplex.getValue(dsOne[k][l])<<endl;
                else
                    cout<<"tbsZero("<<k<<")("<<l<<") or "<<"dsZero("<<k<<")("<<l<<") = "<<"was not add to the model !!!"<<endl;
            }
        }
    }
    cout<<endl;
}

void Extractor::get_NullBlockDiagonalOne(IloCplex cplex)
{
    cout<<endl;
    cout<<"NullBlock with diagonal equals One "<<endl;
    cout<<"Desviation Measuare = block error + diagonal error;"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsOne[k][l]) && cplex.isExtracted(dsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<" + "<<"-"<<" = - "<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsOne[k][l]) && cplex.isExtracted(dsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<<cplex.getValue(tbsOne[k][l])<<" + "<<cplex.getValue(dsZero[k][l])<<" = "<< cplex.getValue(tbsOne[k][l]) + cplex.getValue(dsZero[k][l]) <<endl;
                else
                    cout<<"tbsOne("<<k<<")("<<l<<") or "<<"dsZero("<<k<<")("<<l<<") = "<<"was not add to the model !!!"<<endl;
            }
        }
    }
    cout<<endl;
}

bool Extractor::isEmptyGroup(int k, map<string,clusterGroup>::iterator it)
{
    string key = "C"+ SSTRL(k);
    it = group.find(key);
    clusterGroup g = it->second;
    if (g.size == 0)
    {
        return true;
    }
    return false;
}

void Extractor::get_NullBlockWithoutDiagonal(IloCplex cplex)
{
    cout<<endl;
    cout<<"NullBlock without diagonal "<<endl;
    cout<<"Desviation Measuare = block error ;"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsOne[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsOne[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< cplex.getValue(tbsOne[k][l])<<endl;
                else
                    cout<<"tbsOne("<<k<<")("<<l<<") = "<<"was not add to the model !!!"<<endl;
            }
        }
    }
    cout<<endl;
}

void Extractor::get_CompleteBlockWithoutDiagonal(IloCplex cplex)
{
    cout<<endl;
    cout<<"CompleteBlock without diagonal "<<endl;
    cout<<"Desviation Measuare = (block size - block error) if k!=l else (block size - diagonal size - block error) ;"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<<cplex.getValue(tbsZero[k][l])<<endl;
                else
                    cout<<"tbsZero("<<k<<")("<<l<<") = "<<"was not add to the model !!!"<<endl;
                
            }
        }
    }
    cout<<endl;
}

void Extractor::get_CompleteBlockDiagonalOne(IloCplex cplex)
{
    cout<<endl;
    cout<<"CompleteBlock diagonal one"<<endl;
    cout<<"Desviation Measuare = (block size - block error + diagonal error) if k!=l else (block size - diagonal size - block error + diagonal error) ;"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsZero[k][l]) && cplex.isExtracted(dsZero[k][l]))
                {
                    cout<<"DM("<<k<<")("<<l<<") = "<< cplex.getValue(tbsZero[k][l])<<" + "<< cplex.getValue(dsZero[k][l]) <<" = "<< cplex.getValue(dsZero[k][l]) + cplex.getValue(tbsZero[k][l]) <<endl;
                }
            }
        }
    }
    cout<<endl;
}

void Extractor::get_AllFunctions(IloCplex cplex)
{
    get_AllFunctionsMapping(cplex);
}

void Extractor::get_CompleteBlockDiagonalZero(IloCplex cplex)
{
    cout<<endl;
    cout<<"CompleteBlock diagonal zero"<<endl;
    cout<<"Desviation Measuare = (block error + diagonal error);"<<endl;
    cout<<"NOTE = block error ignores diagonal"<<endl;
    cout<<endl;
    
    map<string,clusterGroup>::iterator it = group.begin();
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if(isEmptyGroup(k,it) || isEmptyGroup(l,it))
            {
                if (cplex.isExtracted(tbsZero[k][l]))
                    cout<<"DM("<<k<<")("<<l<<") = "<< "-"<<endl;
            }
            else
            {
                if (cplex.isExtracted(tbsZero[k][l]) && cplex.isExtracted(dsOne[k][l]))
                {
                    cout<<"DM("<<k<<")("<<l<<") = "<< cplex.getValue(tbsZero[k][l])<<" + " << cplex.getValue(dsOne[k][l])<<" = "<< cplex.getValue(dsOne[k][l]) + cplex.getValue(tbsZero[k][l]) <<endl;
                }
            }
        }
    }
    cout<<endl;
}

void Extractor::get_linesError(IloCplex cplex)
{
    cout<<endl;
    int limit = clusterUpperBound-1;
    
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int p = k; p<networkSize; p++)
            {
                if (cplex.isExtracted(lineError[p][k][l]) && cplex.isExtracted(x[p][k]))
                {
                    if (cplex.getValue(x[p][k])==1)
                    {
                        cout<<"lineError("<<p<<")("<<k<<")("<<l<<") = "<<cplex.getValue(lineError[p][k][l])<<endl;
                    }
                }
                else
                    cout<<"lineError("<<p<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
            }
        }
    }
    cout<<endl;
}

void Extractor::get_omega(IloCplex cplex)
{
    cout<<endl;
    
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int p = 0; p<networkSize; p++)
            {
                if (cplex.isExtracted(omega[p][k][l]))
                {
                    //                    if (cplex.getValue(omega[p][k][l])>0 )
                    //                    {
                    cout<<"omega("<<p<<")("<<k<<")("<<l<<") = "<<cplex.getValue(omega[p][k][l])<<endl;
                    //                    }
                }
                //                else
                //                    cout<<"omega("<<p<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
            }
            cout<<endl;
            
        }
        
    }
}


void Extractor::get_columnError(IloCplex cplex)
{
    cout<<endl;
    
    
    
    
    int limit = clusterUpperBound-1;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        if (itsSymmetricGraph)
            limit = k;
        
        for (int l = 0; l<=limit; l++)
        {
            for (int p = k; p<networkSize; p++)
            {
                if (cplex.isExtracted(columnError[p][k][l]))
                {
                    cout<<"columnError("<<p<<")("<<k<<")("<<l<<") = "<<cplex.getValue(columnError[p][k][l])<<endl;
                }
                else
                    cout<<"columnError("<<p<<")("<<k<<")("<<l<<") =  was not add to the model !!!"<<endl;
                cout<<endl;
            }
        }
    }
    cout<<endl;
}

void Extractor::get_z(IloCplex cplex)
{
    cout<<endl;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            int line = 0;
            
            for (int i = k; i<networkSize; i++)
            {
                if (cplex.isExtracted(z[i][k][l]) && cplex.isExtracted(x[i][k]))
                {
                    //                    if (cplex.getValue(x[i][k])==1)
                    //                    {
                    cout<<"z("<<i<<")("<<k<<")("<<l<<") = "<<cplex.getValue(z[i][k][l])<<endl;
                    line++;
                    //                    }
                }
                else
                    cout<<"z("<<i<<")("<<k<<")("<<l<<") =   was not add to the model !!!"<<endl;
            }
            cout<<endl;
        }
    }
    cout<<endl;
}

void Extractor::get_o(IloCplex cplex)
{
    cout<<endl;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            int line = 0;
            
            for (int i = k; i<networkSize; i++)
            {
                if (cplex.isExtracted(o[i][k][l]) && cplex.isExtracted(x[i][k]))
                {
                    if (cplex.getValue(x[i][k])==1)
                    {
                        cout<<"o("<<line<<")("<<k<<")("<<l<<") = "<<cplex.getValue(o[i][k][l])<<endl;
                        line++;
                    }
                }
                else
                    cout<<"o("<<i<<")("<<k<<")("<<l<<") =   was not add to the model !!!"<<endl;
            }
            cout<<endl;
        }
    }
    cout<<endl;
}



void Extractor::get_h(IloCplex cplex)
{
    cout<<endl;
    for (int k = 0; k<clusterUpperBound; k++)
    {
        for (int l = 0; l< clusterUpperBound; l++)
        {
            if (cplex.isExtracted(h[k][l]))
            {
                cout<<"h("<<k<<")("<<l<<") = "<<cplex.getValue(h[k][l])<<endl;
            }
            else
                cout<<"h("<<k<<")("<<l<<") =   was not add to the model !!!"<<endl;
        }
        cout<<endl;
        
    }
    cout<<endl;
}


void Extractor::get_AllFunctionsMapping(IloCplex cplex)
{
    cout<<endl;
    cout<<"All Functions"<<endl;
    cout<<endl;
    
    vector<vector<string>>result (DataManager::getDataManager()->clusterUpperBound, vector<string>(clusterUpperBound));
    int limit = clusterUpperBound-1;
    
    for (int i =0; i<clusterUpperBound; i++)
    {
        for (int j =0; j<clusterUpperBound; j++)
        {
            result[i][j] ="--";
        }
    }
    
    for(int i=0; i <DataManager::getDataManager()->functionSize; i++)
    {
        FunctionRelease release = DataManager::getDataManager()->functionMapping[i].release;
        
        for(int k=0; k <clusterUpperBound; k++)
        {
            if (release == DIAGONAL)
            {
                
                if (cplex.isExtracted(w[i][k][0]))
                {
                    if (cplex.getValue(emptyCluster[k]!=1))
                        if(cplex.getValue(w[i][k][0]) == 1)
                        {
                            result[k][k] = "F"+ SSTRL(i);
                        }
                }
            }
            else
            {
//                if (itsSymmetricGraph && !DataManager::getDataManager()->areThereNonSymmetricPropertie())
                    if (itsSymmetricGraph )

                    limit = k;
                
                for(int l=0; l <=limit; l++)
                {
                    if (cplex.getValue(emptyCluster[l]!=1))
                        if (cplex.getValue(emptyCluster[k]!=1))
                            if (cplex.isExtracted(w[i][k][l]))
                                if(cplex.getValue(w[i][k][l]) == 1)
                                    result[k][l] = "F"+ SSTRL(i);
                }
            }
        }
    }
    
    for (int i =0; i<clusterUpperBound; i++)
    {
        for (int j =0; j<clusterUpperBound; j++)
        {
            cout<<" "<<result[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    
    cout<<"Table Details:";
    
    // tem uma funçao que chama-se getting mapping, it's better use this one !!!
    for (int p = 0; p<fPSize; p++)
    {
        cout<<" F"+ SSTRL(p)+ " = ";
        get_fIndex(p);
        cout<<";";
    }
    cout<<endl<<endl;
}
